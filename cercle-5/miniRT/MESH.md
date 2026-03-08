# MESH Editor — Full Improvement Plan

## Root-cause Analysis

### Why .rt loads look correct but CLI / popup loads look glitchy

The **`.rt` loading path** (`handle_mesh_injection` → `apply_mesh_material`):

1. Parses explicit `pos / rotation / scale` from the `.rt` token
2. Calls **`mesh_apply_transform(mesh, transform)`** on every sub-mesh which:
   - Bakes the world transform into vertex positions (scale → rotate → translate)
   - Stores a post-bake vertex snapshot in `edit_snap_verts` / `edit_snap_norms`
   - Records `scene_mat` / `scene_rot_mat` (for per-frame skinning world re-apply)
   - Sets `has_scene_transform = true`
   - Resets `mesh->transform` to identity
   - Rebuilds the per-mesh BVH
3. Calls **`clone_instance_materials`** so every `.rt` instance owns independent
   copies of each material (editing one model doesn't corrupt another).

The **CLI / popup path** (`parse_glb` → `editor_add_glb`):

- Calls `parse_glb` directly.  No transform is baked.
- `has_scene_transform` stays **false** → for skinned/animated meshes
  `glb_update_mesh_anim` skips the world-transform re-apply after each
  skinning step, leaving the model in raw GLB local-space (often cm-scale,
  at origin).
- `edit_snap_verts` stays **NULL** → `mesh_transform_sync` returns early;
  transform sliders in the inspector do nothing.
- Materials are **not cloned** → editing one instance changes the material
  for every other mesh that loaded the same GLB.
- The `align_and_frame_meshes` helper (CLI path) sets `transform.pos.y` but
  never bakes it, so the ground-plane can intersect the model.

### Why each GLB appears as N separate scene-panel rows

`parse_glb` creates one `t_mesh` per **primitive** (one material segment per
body part).  A typical character GLB has 10–20 primitives.  The scene panel
iterates `scene->mesh_count`, showing every primitive as its own `[ME] N` row.

### Why the mesh inspector has no Transform tab

`get_tabs()` in `inspector.c` gives meshes `[Info | Material | Physics]`.
`TAB_TRANSFORM` was intentionally omitted, but `mesh_transform_sync` in
`transform_panel.c` is already implemented and works correctly once
`edit_snap_verts` is populated (i.e. after `mesh_apply_transform` is called).

---

## Phase 1 — Fix visual glitch (editor_add_glb)  ✅ immediate

**Files**: `srcs/gui/editor/crud.c`

**Changes**:
- Mirror `editor_add_obj` in `editor_add_glb`:
  - Iterate every newly-added mesh (`mesh_base … mesh_count - 1`)
  - Call `mesh_apply_transform(mesh, mesh->transform)` (identity → no vertex
    change, but sets snapshot + `has_scene_transform = true` + `scene_mat =
    identity`)
  - Call `scene_clone_material` for each sub-mesh so materials are instance-
    owned

**Why identity is fine here**: the user then moves / scales the mesh via the
inspector (Phase 2).  The model appears at its GLB-local position (usually
centred near origin), which is correct as a starting point.

**CLI fix** (`srcs/objects/rt/parser/utils.c` → `align_and_frame_meshes`):
- Instead of only setting `transform.pos.y`, also call
  `mesh_apply_transform(mesh, mesh->transform)` after updating the pos — so
  the baked Y offset actually moves the mesh vertices above the floor plane.

---

## Phase 2 — Transform tab in mesh inspector  ✅ immediate

**Files**: `srcs/gui/editor/inspector.c`

**Change**: add `TAB_TRANSFORM` as the first tab for `TYPE_MESH`:
```
[Transform | Info | Material | Physics]
```
`mesh_transform_sync` already drives sliders correctly once Phase 1 is done.

---

## Phase 3 — Single entry per GLB in scene panel

**Strategy**: introduce a lightweight **mesh group** concept.

### Data model (objects.h / scene.h)

```c
/* in s_mesh */
int  group_id;   /* -1 = standalone; ≥0 = group index */

/* in t_scene */
int  mesh_group_count;
```

### Assignment rules

| Loader | group_id |
|---|---|
| `parse_glb` (runtime) | `scene->mesh_group_count` for all new meshes, then `++` |
| `parse_obj`, `parse_fdf`, `parse_fbx` | `-1` (each mesh is standalone) |
| Primitive shapes (sphere, plane …) | n/a — not in `meshes[]` |

### Scene-panel changes

- `count_scene_rows`: count unique group IDs + standalone meshes (instead of
  raw `mesh_count`)
- `row_to_object`: map a row index to the **first** mesh of a group (or a
  standalone mesh)
- Show label: `[ME] <basename>` (strip path + extension from `mesh->name`),
  e.g. `[ME] stylized_women`

### Selection / transform

- `gui->selection.index` points to the **first** mesh of the group
- `mesh_transform_sync` is extended to apply transform changes to **all**
  meshes sharing the same `group_id`
- Delete: removes all meshes in the group

---

## Phase 4 — Material editing per submesh

### Problem

A GLB model can have 10–20 distinct materials (one per body part / primitive).
The material tab currently only edits the material of the single selected
`mesh->mat_id`, whereas a group selection points at the first mesh only.

### Solution: submesh picker inside Material tab

When the selected object is a mesh group:

1. Draw a small **Submesh selector** row inside the Material tab:
   `< Submesh 3 / 12 >` (prev / next arrow buttons)
2. The selected submesh index is stored in a new `gui->inspector.submesh_idx`
   field.
3. `get_selected_material` is extended: for `TYPE_MESH` groups, it returns the
   material at `scene->meshes[first + submesh_idx].mat_id`.

### Material overrides (smart approach)

GLB materials can have PBR textures (albedo map, normal map, etc.).  Instead
of replacing those entirely, expose a minimal **override** layer:

| Override | Effect |
|---|---|
| **Color tint** (RGB 0–1) | Multiplied with `albedo_map.color_a` at shading |
| **Emission scale** (0–10) | Multiplied with `material.emission` |
| **Roughness** (0–1) | Replaces `material.roughness` if ≥ 0 |
| **Metalness** (0–1) | Replaces `material.metalness` if ≥ 0 |

These overrides are stored directly inside `t_material` (no new fields needed
since `albedo_map.color_a`, `emission`, `roughness`, `metalness` already
exist).  Editing them via the material panel already works — the only missing
piece is the submesh picker to choose which sub-mesh to edit.

---

## Implementation schedule

| Phase | Scope | Files | Risk |
|---|---|---|---|
| Phase 1 | visual glitch + clone materials | `crud.c`, `utils.c` | low |
| Phase 2 | Transform tab for mesh | `inspector.c` | trivial |
| Phase 3 | Group concept + panel | `objects.h`, `scene.h`, `glb/parser.c`, `scene_panel.c`, `transform_panel.c` | medium |
| Phase 4 | Submesh material picker | `inspector.c`, `material_panel.c`, `gui.h` | medium |

Each phase is committed independently with a `git add -A && git commit`.
