# lazy.md — Mini-RT Mesh UX Fixes

## Issues to Fix

### 1. Reset (`R`) should remove popup/CLI-added meshes

**Root cause:**
`scene_reset()` in `scene_reset.c` restores transforms for `snap->mesh_count`
meshes but never truncates `sc->mesh_count`. Meshes added via the editor popup
beyond the original set persist indefinitely after reset.

`t_scene_snap` also doesn't snapshot `mesh_group_count`, so group IDs would
start from wherever they were left, rather than the post-parse baseline.

**Fix:**
- Add `int mesh_group_count` to `t_scene_snap` (editor.h).
- `scene_snap_take`: capture `snap->mesh_group_count = sc->mesh_group_count`.
- `scene_reset`: call `mesh_free` on each mesh beyond `snap->mesh_count`,
  then truncate `sc->mesh_count = snap->mesh_count` and restore
  `sc->mesh_group_count = snap->mesh_group_count`.

**Caching on every import (same request):**
`editor_add_glb` currently calls `parse_glb` unconditionally, bypassing the
existing `mesh_cache_has / mesh_cache_restore / mesh_cache_save` system that
`injection.c` already uses for the `.rt` path. Every re-import or cross-map
reuse triggers a full re-parse.

**Fix (crud.c `editor_add_glb`):**
- If `mesh_cache_has(path)`: restore from cache, then assign a fresh `group_id`
  (cache restore doesn't do this).
- Else: call `parse_glb` (which increments `mesh_group_count` and assigns
  `group_id` itself), then `mesh_cache_save` the result.

---

### 2. Only part of the mesh moves when dragging position sliders

**Root cause (scale = 0 bug):**
`parse_glb` → `init_mesh` does `ft_memset(mesh, 0)` — leaving
`mesh->transform.scale = {0, 0, 0}`.

`editor_add_glb` then calls:
```c
mesh_apply_transform(&scene->meshes[i], scene->meshes[i].transform);
```
with scale = 0.  `mat4_scaling({0,0,0})` produces a zero matrix → every vertex
collapses to the translation point → `edit_snap_verts` captures *zeroed*
vertices instead of the real geometry snapshot.

From that moment, dragging position works for vertices whose formula cancels
(all collapse to the pivot point + pos), but the rendered triangles degenerate.
The effect looks like "only part moving" — some submeshes may have
`edit_snap_verts = NULL` (skipped) while the leader collapses to a point.

Same bug exists in `align_and_frame_meshes` (the CLI path):
```c
scene->meshes[i].transform.pos.y += offset_y;
mesh_apply_transform(&scene->meshes[i], scene->meshes[i].transform); // scale=0!
```

**Fix:**
- In `editor_add_glb` loop: force identity scale before `mesh_apply_transform`.
  GLB vertices are already in world space — we just need an identity bake.
- In `align_and_frame_meshes`: set `mesh->transform.scale = vec3(1,1,1)` before
  calling `mesh_apply_transform`.
- In `cache.c` `restore_one`: set `mesh.group_id = -1` (restore currently
  inherits 0 from memset; editor_add_glb re-assigns anyway but -1 is the safe
  sentinel).

---

### 3. Inspector: Info tab before Transform tab for meshes

**Root cause:** Tab array in `inspector.c` `get_tabs()` for `TYPE_MESH` is
`[Transform | Info | Material | Physics]`. User prefers `Info` first.

**Fix:** Swap to `[Info | Transform | Material | Physics]`.

---

## Files to change

| File | Change |
|---|---|
| `includes/editor.h` | Add `int mesh_group_count` to `t_scene_snap` |
| `srcs/gui/editor/scene_reset.c` | snap_take captures group_count; reset frees extra meshes + truncates |
| `srcs/gui/editor/crud.c` | `editor_add_glb`: cache check, group_id assign for restore path, scale=1 fix |
| `srcs/objects/rt/parser/utils.c` | `align_and_frame_meshes`: scale=1 before `mesh_apply_transform` |
| `srcs/objects/rt/mesh/cache.c` | `restore_one`: set `mesh.group_id = -1` |
| `srcs/gui/editor/inspector.c` | Mesh tabs: Info first, then Transform |

## Commit plan

```
fix(mesh): reset removes editor-added meshes + import cache
fix(mesh): identity-scale bake fixes submesh movement
fix(ux): mesh inspector — Info tab first
```
All three can go in one commit: `fix(mesh): reset/cache/movement/tabs`
