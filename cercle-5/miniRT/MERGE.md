# MERGE — Unifying the Direct-Load and RT-Parse Paths

## Problem Statement

When the user passes a raw mesh file:
```
./miniRT maps/glb/leggings_girl.glb
```
the app hits a **separate, parallel build routine** in `parse_by_ext` instead of
routing through the battle-tested `.rt` parser pipeline.  The result is a
second code path that does **less** than the RT path while being **harder to
maintain**.

---

## The Two Paths Today

### RT path (`./miniRT maps/rt/torn_girl.rt`)

```
parse_file()
  └─ parse_by_ext(ext="rt")
       └─ parse_rt(path, scene)           ← line-by-line RT parser
            └─ rt_parse_loop()
                 └─ rt_parse_entry() / "glb path …" line
                      └─ handle_mesh_injection()
                           ├─ parse_glb()                   ← geometry
                           ├─ mesh_cache_save()             ← cache for next instance
                           ├─ clone_instance_materials()    ← per-instance mats
                           ├─ apply_mesh_material()
                           │    └─ mesh_apply_transform()   ← single, correct bake
                           └─ scene_add_group_for_subs()    ← t_mesh_group created
```

Camera, ambient, lights, floor plane all come from explicit RT lines.

### Direct path (`./miniRT maps/glb/leggings_girl.glb`) — **BROKEN**

```
parse_file()
  └─ parse_by_ext(ext="glb")
       ├─ setup_default_scene()     ← programmatic scene setup (ambient/lights/plane)
       ├─ parse_glb()               ← geometry only — bypasses handle_mesh_injection
       └─ align_and_frame_meshes()  ← Y-offset bake + camera framing
```

**What the direct path is missing vs the RT path:**

| Feature | RT path | Direct path |
|---------|---------|-------------|
| `mesh_cache_save` | ✅ | ❌ no caching |
| `clone_instance_materials` | ✅ | ❌ materials shared, not per-instance |
| `apply_mesh_material` transform bake | ✅ single bake | ⚠️ via align_and_frame (only Y) |
| `scene_add_group_for_subs` → `t_mesh_group` | ✅ | ❌ **groups[] is empty** |
| Editor inspector (transform/material tabs) | ✅ works | ❌ **completely broken** |
| `align_and_frame_meshes` (auto-camera) | ❌ not needed | ✅ done |

The critical breakage: **`scene->groups[]` is never populated** in the direct
path.  All Phase-B editor code (`transform_panel.c`, `material_panel.c`,
`scene_panel.c`, `selection.c`) operates on `scene->groups[]`.  When
loading a GLB directly, the inspector shows nothing and transforms/material edits
are inoperative.

---

## Root Cause

`parse_by_ext` for non-RT files calls the low-level `parse_glb / parse_obj /
parse_fdf / parse_fbx` functions **directly**, bypassing
`handle_mesh_injection` — the layer that does caching, material cloning, group
registration, and transform baking.

`setup_default_scene` is a parallel re-implementation of what a four-line RT
preamble block would produce, duplicating maintenance burden.

---

## The Fix: Route Direct Loads Through the RT Pipeline via a Virtual Scene

### Concept

Instead of a parallel build routine, generate a minimal RT scene string in
memory for any direct mesh load, feed it through the existing RT parser via a
pipe fd, then run `align_and_frame_meshes` as a post-parse step (the only thing
the direct path adds that RT files don't need).

```
parse_by_ext(ext="glb", path, scene)
  └─ parse_as_default_rt("glb", path, scene)   [NEW — replaces setup_default_scene + parse_glb]
       ├─ snprintf → RT content string:
       │     A 0.3 255,255,255
       │     C 0,0,30 0,0,-1 70
       │     L -30,200,30 0.8 255,255,255
       │     L -15,40,10 0.8 100,50,30
       │     L 0,60,-20 0.8 100,50,30
       │     pl 0,0,0 0,1,0 150,150,150
       │     glb maps/glb/leggings_girl.glb 0,0,0 0,0,0 1.0
       ├─ pipe(fds)
       ├─ write(fds[1], content, len) ; close(fds[1])
       └─ parse_rt_fd(fds[0], scene)           [NEW — fd variant of parse_rt]
            └─ handle_mesh_injection()          ← full pipeline: cache, mats, group, bake
  └─ align_and_frame_meshes(scene, start_idx)  ← Y-offset + camera framing (unchanged role)
```

### Key insight: the identity bake is safe

`handle_mesh_injection` bakes the transform from the RT line (`pos=0, rot=0,
scale=1`) — an **identity transform** — so vertices are unchanged.  Then
`align_and_frame_meshes` performs the real bake (Y-offset translation).
Two bakes are safe because the first is the identity matrix.

### What needs fixing after the two-bake situation

After the second bake in `align_and_frame_meshes`, two stale values need refresh:

1. **`mesh->edit_snap_verts/norms/pivot`** — set by the first (identity) bake
   inside `mesh_apply_transform`.  If stale, the editor's first drag operation
   "resets" vertices to the pre-Y-offset position, causing a visible jump.

2. **`g->pivot` in `t_mesh_group`** — computed by `scene_add_group_for_subs`
   in model-space (Y=0).  After the Y-bake the pivot centre is off by
   `offset_y`, breaking gizmo/inspector display.

Both are refreshed **inside** `align_and_frame_meshes` with a small loop after
the bake.

---

## Files Changed

| File | Change |
|------|--------|
| `srcs/objects/rt/parser/parse.c` | Add `parse_rt_fd(int fd, t_scene *)` |
| `srcs/objects/rt/parser/utils.c` | Remove `setup_default_scene`; add `parse_as_default_rt`; rewrite `parse_by_ext`; fix `align_and_frame_meshes` (snap + pivot refresh) |
| `includes/objects.h` | Declare `parse_rt_fd` |

---

## What Is Preserved

- `align_and_frame_meshes` logic (Y-floor bake + camera framing) — the only
  "extra" the direct path legitimately needs
- All RT parsing logic untouched — `parse_rt`, `handle_mesh_injection`, etc.
- `parse_rt(path, scene)` unchanged for normal `.rt` file loads
- Zero behaviour change for `.rt` maps

## What Is Deleted

- `setup_default_scene` — superseded by the generated RT preamble
- The four direct `parse_glb / parse_obj / parse_fdf / parse_fbx` call sites in
  `parse_by_ext` — they now go through `handle_mesh_injection` via the RT
  pipe
