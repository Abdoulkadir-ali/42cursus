# MESH — Architecture & Improvement Plan

Phases 1–3 are committed.  This document records what remains: a confirmed
bug, the structural debt that enables it, and the refactor plan.

---

## Current state (post Phase 3)

### group_id integer tag system

Every `t_mesh` carries an integer `group_id`:
- `-1` = standalone (OBJ / FBX / FDF or any non-group mesh)  
- `≥ 0` = all submeshes that came from the same GLB file share one value

Code that needs to operate on a whole group must scan `scene->meshes[0..n]`
looking for `m->group_id == gid`.  This pattern appears in `scene_panel.c`,
`transform_panel.c`, and `scene_reset.c`.

### Where group_id is assigned

| Call path | group_id assigned? | notes |
|-----------|-------------------|-------|
| `parse_glb` (direct, fresh parse) | ✅ at the bottom of `parse_glb` | `scene->mesh_group_count++` |
| `editor_add_glb` (cache hit) | ✅ in `crud.c` after restore | explicit loop |
| `handle_mesh_injection` (fresh parse) | ✅ via `parse_glb` internally | |
| **`handle_mesh_injection` (cache hit)** | ❌ nobody assigns it | **BUG** |

---

## Phase A — Immediate bug fix  ✅ DONE

**File**: `srcs/objects/rt/mesh/injection.c`

**Problem**: when the same GLB is referenced twice in a `.rt` file, the second
load takes the cache-hit branch.  `mesh_cache_restore` calls `restore_one` for
each sub-mesh, which resets `group_id = -1`.  Nothing in
`handle_mesh_injection` reassigns a fresh `gid`.

`mesh_transform_sync` checks:
```c
if ((gid < 0 && m != lead) || (gid >= 0 && m->group_id != gid))
    continue;
```
With all sub-meshes at `group_id = -1` and `lead->group_id = -1`, every mesh
except the lead is skipped → only the first sub-mesh moves.

**Fix** (one block, mirroring `editor_add_glb`):
```c
if (mesh_cache_has(path))
{
    mesh_cache_restore(path, scene);
    /* reassign fresh gid — restore_one resets to -1 */
    int gid = scene->mesh_group_count++;
    int mi  = start_mesh;
    while (mi < scene->mesh_count)
        scene->meshes[mi++].group_id = gid;
}
```

---

## Structural debt — why this bug was possible

### t_mesh carries group-level state

`t_mesh` is used for both "a submesh (one primitive of one GLB node)" and "a
standalone mesh (one OBJ file)".  It mixes three unrelated concerns:

**Geometry + rendering** — belongs on every submesh:
```
name, vertices, normals, uvs, indices
vertex_count, tri_count, bbox
bvh_nodes, bvh_indices, tri_cache
mat_id
```

**Per-submesh animation** — belongs here but is messy:
```
skin_data, skeleton, bone_count, bone_matrices
base_vertices, base_normals, node_idx
scene_mat, scene_rot_mat, has_scene_transform
current_anim, anim_time
```

**Group-level state** — does NOT belong on a submesh:
```
transform          ← one per group, not per primitive
phys               ← one physics body per group
collider           ← same
edit_snap_verts    ← must be group-coordinated (shared pivot)
edit_snap_norms
edit_snap_pivot    ← must be shared or it rotates around different centres
group_id           ← the integer tag itself
anim_base          ← same clip range on every submesh (duplicated)
anim_clip_count    ← same
```

Every submesh duplicates transform, phys, collider, anim_base/count.
If an N-mesh GLB is in the scene, N copies of `t_physics_body` exist but only
the one on `meshes[lead_idx]` is ever used.

### s_skinned_mesh duplicates t_mesh fields

```c
struct s_skinned_mesh {
    t_mesh         base;          // already has: skeleton, bone_matrices,
                                  //   bone_count, base_vertices, vertex_count
    t_vec3        *base_vertices; // DUPLICATE
    t_bone        *skeleton;      // DUPLICATE
    t_mat4        *bone_matrices; // DUPLICATE
    t_bone_weight *weights;       // = base.skin_data (different name, same data)
    int            bone_count;    // DUPLICATE
    int            vertex_count;  // DUPLICATE
};
```

`s_skinned_mesh` is stored in `scene->animated[]`, creating a second array
that only the animation system knows about.  Code that wants to find a mesh by
its scene index cannot use a single array; it has to check `animated[]` too.
At the moment `animated[]` is effectively unused — all animation happens on
`meshes[]` — but the struct still exists and confuses anyone reading the code.

### scene->meshes[] + scene->animated[] split

```c
t_mesh         *meshes;   int mesh_count;
t_skinned_mesh *animated; int anim_count;
```

Two parallel arrays for what is conceptually one list of models.  Selecting by
scene-panel row, resetting the scene, and rendering all have to touch both
arrays.  Currently only `meshes[]` is populated (animated GLB submeshes are
stored there too), making `animated[]` dead weight.

---

## Phase B — Architectural refactor (planned, not started)

### Goal

All group-level state lives in exactly one place.  No scanning.  Forgetting to
set `group_id` becomes impossible because `group_id` no longer exists.

### New container: t_mesh_group

```c
typedef struct s_mesh_group
{
    char            *name;          /* display name (GLB basename) */
    char            *path;          /* source file path */
    t_mesh          *subs;          /* owned, contiguous array of submeshes */
    int              sub_count;
    t_transform      transform;     /* ONE shared transform (pos/rot/scale) */
    t_vec3           pivot;         /* shared pivot for SR+T in editor */
    t_vec3         **snap_verts;    /* [si] → post-bake snapshot for subs[si] */
    t_vec3         **snap_norms;
    t_physics_body   phys;
    t_collider       collider;
    int              anim_base;
    int              anim_clip_count;
} t_mesh_group;
```

### t_mesh reduced to pure geometry + per-primitive rendering

```c
struct s_mesh
{
    char             *name;
    t_vec3           *vertices;
    t_vec3           *normals;
    t_vec2           *uvs;
    int              *indices;
    int               vertex_count;
    int               tri_count;
    t_aabb            bbox;
    t_mbvh_node      *bvh_nodes;
    int              *bvh_indices;
    t_tri_precomp    *tri_cache;
    int               mat_id;
    /* skinning (per-primitive, only set on rigged meshes) */
    t_bone_weight    *skin_data;
    t_bone           *skeleton;
    int               bone_count;
    t_mat4           *bone_matrices;
    t_vec3           *base_vertices;
    t_vec3           *base_normals;
    int               node_idx;
    t_mat4            scene_mat;
    t_mat4            scene_rot_mat;
    bool              has_scene_transform;
    double            anim_time;
    /* REMOVED: transform, phys, collider, group_id,
                edit_snap_verts, edit_snap_norms, edit_snap_pivot,
                anim_base, anim_clip_count, current_anim */
};
```

### t_scene simplified

```c
/* before */
t_mesh         *meshes;   int mesh_count;  int mesh_cap;  int mesh_group_count;
t_skinned_mesh *animated; int anim_count;  int anim_cap;

/* after */
t_mesh_group   *groups;   int group_count; int group_cap;
/* s_skinned_mesh removed entirely */
```

### transform sync — no scan needed

```c
static void group_transform_sync(t_mesh_group *g)
{
    t_mat4  s  = mat4_scaling(g->transform.scale);
    t_mat4  r  = mat4_rotation(g->transform.rotation);
    t_mat4  sr = mat4_mul(r, s);
    for (int si = 0; si < g->sub_count; si++)
    {
        t_mesh *m = &g->subs[si];
        for (int vi = 0; vi < m->vertex_count; vi++)
        {
            t_vec3 local = vec3_sub(g->snap_verts[si][vi], g->pivot);
            local = mat4_mul_pos(sr, local);
            m->vertices[vi] = vec3_add(vec3_add(local, g->pivot),
                                       g->transform.pos);
            if (m->normals && g->snap_norms[si])
                m->normals[vi] = vec3_norm(mat4_mul_vec3(r, g->snap_norms[si][vi]));
        }
        m->bbox = aabb_from_mesh(m);
        mesh_build_bvh(m);
    }
}
```

No `gid` integer, no scan, no "forgot to set group_id" class of bug.

### Files to change (Phase B)

| File | Change |
|------|--------|
| `includes/objects.h` | Add `t_mesh_group`; strip group fields from `t_mesh`; remove `s_skinned_mesh` |
| `includes/scene.h` | Replace `meshes+animated` with `groups` |
| `srcs/objects/glb/parser.c` | Fill `t_mesh_group` instead of flat array; BVH per sub |
| `srcs/objects/mesh/init.c` | Remove `group_id` init; update `mesh_free` |
| `srcs/objects/rt/mesh/cache.c` | Cache/restore `t_mesh_group` (geometry only) |
| `srcs/objects/rt/mesh/injection.c` | Remove group_id block; populate group struct |
| `srcs/gui/editor/crud.c` | `editor_add_glb` → add `t_mesh_group` to scene |
| `srcs/gui/editor/transform_panel.c` | Replace scan with `group_transform_sync` |
| `srcs/gui/editor/scene_panel.c` | Iterate `scene->groups` directly |
| `srcs/gui/editor/scene_reset.c` | Reset `group_count` to snap |
| `srcs/gui/editor/selection.c` | Select a `t_mesh_group` by index |
| `srcs/rays/raytracing/intersect_mesh.c` | Iterate group subs |
| `srcs/physics/**` | Operate on `group->phys` and `group->collider` |

Estimated risk: **medium-high** (touches raytracer, physics, and animation
frame loop).  Implement in isolation on a feature branch; keep Phase A live on
main in the meantime.

---

## What NOT to do prematurely

- Do not merge `s_skinned_mesh` first in isolation — it is only meaningful
  once the group container owns the animation clips.
- Do not convert `scene->animated[]` to `scene->groups[]` without simultaneously
  updating the animation frame loop (`glb_update_mesh_anim`).
- Do not add more fields to `t_mesh` that belong on a group.

---

## Implementation order (Phase B)

1. Define `t_mesh_group` in `objects.h`, leave `t_mesh` untouched.
2. Add `scene->groups` alongside existing `meshes` array (keep both working).
3. Port `parse_glb` → populate one `t_mesh_group` using the flat array it already builds.
4. Port `editor_add_glb` and `handle_mesh_injection` to use `groups`.
5. Port `scene_panel`, `transform_panel`, `scene_reset`, `selection`.
6. Port raycaster (`intersect_mesh`) to iterate `groups[i].subs[j]`.
7. Port physics and animation loops.
8. Remove `meshes` array, remove `group_id` from `t_mesh`, remove `s_skinned_mesh`.
9. Compile, run all test maps.

Each numbered step is one commit.
