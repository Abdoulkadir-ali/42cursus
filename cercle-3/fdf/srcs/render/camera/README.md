# Camera Module

Handles camera creation, default state seeding, and map-source attachment. This subsystem is responsible for producing a ready-to-use `t_camera_manager` that binds the active camera, the selected map, and the window context before the render pipeline starts.

---

## Directory Structure
- `srcs/render/camera/` — Camera setup root
- `init.c` — Camera default initialization and top-level camera manager creation
- `map_init.c` — Map source selection and camera-manager allocation helpers
- `controls/` — Runtime camera manipulation helpers

---

## How It Works

### Global Pipeline
1. The core startup path calls `init_camera_and_graphics` from `srcs/core/helper.c`.
2. That function builds a `t_camera_args` bundle and forwards it to `init_camera`.
3. `init_camera` first allocates a `t_camera_manager` through `allocate_camera_manager`.
4. `allocate_camera_manager` allocates both the manager and the owned `t_camera`.
5. It seeds the camera through `init_camera_default`.
6. If a window is already available, it places the initial camera offset at the window center.
7. Control returns to `init_camera`, which resolves the map source through `setup_map_source` when a map manager is present.
8. `setup_map_source` chooses one of three sources: directory list, single file, or generated test grid.
9. Once the active map is known, `init_camera` stores it in `ctx->map`.
10. It then computes the initial rotation matrix through `update_rotation_matrix`.
11. It finishes by computing the camera transform matrix through `calculate_transform_matrix`.
12. The initialized camera manager is returned to the core startup code, which then creates the graphics context around the same camera.

### `init.c`
- `init_camera_default` writes the baseline camera state into an already allocated `t_camera`.
- It seeds rotation, offset, grid center, color shift, projection mode, scale controls, z-scale, frustum margin, movement flags, alpha, and target rotation.
- `init_camera` is the folder entry point.
- It owns the handoff from allocation to map attachment to matrix preparation.

#### Pipeline Inside `init.c`
1. `init_camera` calls `allocate_camera_manager(args)`.
2. If allocation fails, it returns `NULL`.
3. If no external map manager is supplied, it simply stores `args.map` in `ctx->map` and returns.
4. Otherwise it keeps a local pointer to `args.manager`.
5. It calls `setup_map_source(mgr, args)`.
6. If map setup fails, it frees the owned camera and manager before returning `NULL`.
7. On success it copies `mgr->current_map` into `ctx->map`.
8. It updates the cached rotation matrix.
9. It computes the transform matrix used later by projection code.

### `map_init.c`
- Owns the policy for where the camera gets its map from.
- Bridges the camera layer with the map-loading logic from `srcs/geometry/map/read`.

#### Pipeline Inside `map_init.c`
1. `setup_map_source` checks whether `args.map_file` is present.
2. If a path is present and is a directory, it calls `init_map_list(mgr, args.map_file)`.
3. If a path is present and is not a directory, it calls `init_manager_with_file(mgr, args.map_file)`.
4. `init_manager_with_file` loads the map immediately through `load_map`.
5. It then allocates single-entry `map_files` and `maps` arrays and stores the loaded map as index `0`.
6. If no path is provided but the manager already owns maps, `setup_map_source` resets `current_index` to `0` and selects the first map.
7. If no usable source exists, it falls back to `init_manager_with_test_grid`.
8. `init_manager_with_test_grid` creates one generated grid and exposes it as the current map.

#### Ownership Notes
- `allocate_camera_manager` owns the `t_camera_manager` allocation and the nested `t_camera` allocation.
- `init_manager_with_file` turns a single file path into a one-element map inventory so the rest of the program can treat file and directory sources uniformly.
- `setup_map_source` does not build transform data itself; it only guarantees that `mgr->current_map` is ready before control returns to `init_camera`.

---

## Developer Notes
- This folder is startup-focused: it creates camera state, but it does not handle user-driven movement or zoom updates.
- Runtime camera manipulation lives in `srcs/render/camera/controls`.
- Matrix updates are delegated to the rotate submodule before the projection pipeline consumes the camera.
- The camera manager is the shared handle passed into the core, event, GUI, and render layers.

For detailed function documentation, see the source files and declarations in `includes/render.h`.