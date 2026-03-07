# Plan: Dress/Accessory Animation Synchronization (No-Realloc)

## Problem
Skinned body meshes animate correctly. Non-skinned accessory meshes (dress, cloth, hair)
stay static because `glb_skin_mesh()` is gated on `mesh->skin_data != NULL`.
These accessories are rigid-parented in the GLTF scene graph — no weights, just a node transform.

---

## Memory Safety Approach: No Realloc

**Key insight**: Instead of allocating N bones then realloc-ing to N+extra,
we count the extra nodes BEFORE allocating, then `malloc` the full final size once.

```
extra_count = glb_count_extra_anim_nodes(json, skin_joints, joint_count)
glb_load_skeleton(&mesh, json, bin, extra_count)   // malloc N + extra_count upfront
glb_fill_extra_anim_nodes(&mesh, json)             // fill slots [N .. N+extra-1]
finalize_mesh(scene, &mesh, path)                  // scene_add_mesh after all writes
```

No pointer ever changes after the initial malloc. No realloc. No dangling pointer risk.

### Other safety rules
- `scene_add_mesh` is a VALUE COPY — must happen after all writes to the mesh struct.
- `t_mesh_snap` caches only geometry — no skeleton fields, nothing to change there.
- `load_channels` calls `!strcmp(path, ...)` — `path` can be NULL → must guard.

---

## Steps

### Step 1 — Crash fix: NULL guard in `load_channels` (anim_load.c)
In `load_channels`, before the strcmp chain:
```c
if (!path) { anim->channels[i].path = PATH_WEIGHTS; continue; }
```
Build and run. Crash disappears. Nothing else changes.

---

### Step 2 — Add fields to structs (objects.h)
- `int node_idx` to `struct s_mesh` — which GLTF node owns this mesh (-1 = none)
- `t_mat4 global_transform` to `t_bone` — world matrix stored during bone update

`init_mesh` zeroes the struct, so we explicitly set `mesh.node_idx = -1` in parser.
`t_mesh_snap` unchanged (only caches geometry).

---

### Step 3 — Count extra animated nodes (new function in skeleton.c)
`int glb_count_extra_anim_nodes(t_json_value *json, t_json_value *joints)`

- Builds a `known[65536]` boolean array of all joint node indices (stack or ft_calloc)
- Walks animation channels, counts nodes NOT in `known`
- Returns the count (0 if none)
- No mesh modification, no allocations that outlive the function

---

### Step 4 — Modified `glb_load_skeleton` takes `extra_count` (skeleton.c)
Signature: `glb_load_skeleton(t_mesh *mesh, t_json_value *json, char *bin, int extra_count)`

Change only the malloc lines:
```c
mesh->skeleton    = malloc(sizeof(t_bone) * (count + extra_count));
mesh->bone_matrices = malloc(sizeof(t_mat4) * (count + extra_count));
mesh->bone_count  = count;   // still just the joints for now
```
Extra slots exist but are uninitialised — filled in Step 5.

---

### Step 5 — Fill extra slots (new function in skeleton.c)
`void glb_fill_extra_anim_nodes(t_mesh *mesh, t_json_value *json)`

- Rebuilds `known[65536]` from existing joints
- Walks channels again, for each unknown node:
  - `ft_memset` the slot at `mesh->skeleton[mesh->bone_count]`
  - Set `node_idx`, `parent = -1`, `inv_bind_pose = identity`
  - Read TRS from GLTF node JSON
  - Set `bone_matrices[mesh->bone_count] = identity`
  - Increment `mesh->bone_count`
- Free `known`

---

### Step 6 — Set `mesh.node_idx` in parser (parser.c)
For non-skinned primitives (no `skin_data`): walk GLTF nodes, find the node whose
`"mesh"` field equals the mesh index `i`, store that node index in `mesh.node_idx`.
Read-only JSON walk, no allocations.

Call order:
```
extra_count = glb_count_extra_anim_nodes(json, joints)
glb_load_skeleton(&mesh, json, bin, extra_count)
glb_fill_extra_anim_nodes(&mesh, json)
// set mesh.node_idx for non-skinned
finalize_mesh(scene, &mesh, path)
```

---

### Step 7 — Rigid transform in `glb_update_mesh_anim` (anim_system.c)
In `update_bone_recursive`, store: `bone->global_transform = global;`

After the bone tree update, before `glb_skin_mesh`:
```
if mesh->skin_data == NULL and mesh->node_idx >= 0 and mesh->base_vertices != NULL:
    find bone with node_idx == mesh->node_idx
    apply its global_transform rigidly to all base_vertices → vertices
    apply same Z→Y axis swap as glb_skin_mesh
```

---

## File Touch Map

| File | Change |
|------|--------|
| `srcs/objects/glb/anim_load.c` | Step 1: NULL guard |
| `includes/objects.h` | Step 2: `node_idx` in `t_mesh`, `global_transform` in `t_bone` |
| `srcs/objects/glb/skeleton.c` | Steps 3+4+5: count, modified alloc, fill |
| `srcs/objects/glb/parser.c` | Step 6: set `mesh.node_idx`, pass `extra_count` |
| `srcs/objects/glb/anim_system.c` | Step 7: store global, rigid transform branch |

## Test After Each Step

- Step 1: `./miniRT maps/rt/torn_girl.rt` → no crash
- Step 2: build clean, no regression
- Steps 3-6: debug print `mesh->bone_count` before/after fill
- Step 7: dress follows body
