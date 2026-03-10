# Camera Rotate Submodule

Handles camera rotation-matrix construction and vector rotation helpers. This submodule is responsible for turning the current camera rotation state into a cached 3x3 matrix that the projection and cache layers can reuse across the frame.

---

## Directory Structure
- `srcs/render/camera/controls/rotate/` — Rotation helper root
- `build.c` — Builds the three axis rotation matrices
- `init.c` — Prepares the trigonometric context and triggers matrix composition
- `multiply.c` — Matrix-matrix and matrix-vector multiplication helpers
- `rotate.c` — Applies the cached camera rotation matrix to one vector

---

## How It Works

### Global Pipeline
1. Camera startup or later camera updates call `update_rotation_matrix`.
2. `update_rotation_matrix` reads the current rotation fields from `t_camera`.
3. It builds a `t_rot_ctx` containing the raw rotation values and their sine and cosine values.
4. It forwards that context to `compose_rotation_matrix`.
5. `compose_rotation_matrix` builds the X, Y, and Z axis matrices through `build_rotation_matrices`.
6. It multiplies those matrices into one final 3x3 rotation matrix.
7. The result is stored in `cam->rotation_matrix`.
8. Projection code later consumes that cached matrix when computing the full transform matrix and when rotating points into camera space.

### `build.c`
- Contains the axis-specific matrix builders.
- `build_rx`, `build_ry`, and `build_rz` each fill one 3x3 basis matrix.
- `build_rotation_matrices` is the exported helper that writes all three axis matrices from one prepared `t_rot_ctx`.

### `init.c`
- Owns context preparation for matrix construction.

#### Pipeline Inside `init.c`
1. `update_rotation_matrix` validates the camera pointer.
2. It creates a local `t_rot_ctx`.
3. `init_rot_ctx` copies `cam->rotation` into `ctx.rot`.
4. It computes `cos()` and `sin()` for each axis and stores them in `ctx.cos` and `ctx.sin`.
5. `update_rotation_matrix` then calls `compose_rotation_matrix(cam, &ctx)`.

### `multiply.c`
- Owns the composition step that turns the three axis matrices into the cached camera matrix.

#### Pipeline Inside `multiply.c`
1. `compose_rotation_matrix` allocates local `rx`, `ry`, `rz`, `tmp`, and `out` arrays.
2. It fills `rx`, `ry`, and `rz` through `build_rotation_matrices`.
3. It multiplies `ry` by `rz` into `tmp`.
4. It multiplies `rx` by `tmp` into `out`.
5. It copies the final rows into `cam->rotation_matrix[0..2]`.

#### Helper Roles
- `mat_mul` multiplies two 3x3 matrices stored as three row vectors.
- `mat_vec_mul` multiplies one 3x3 matrix by one vector and writes the result through an output pointer.

### `rotate.c`
- Exposes `apply_rotation_with_matrix`.
- This helper reads the cached `cam->rotation_matrix` and applies it to one `t_vec3d`.
- It returns the input vector unchanged if the camera pointer is `NULL`.
- The file keeps its own internal matrix-vector multiply helper local to the translation unit.

### Runtime Handoff
1. `update_rotation_matrix` is used during camera initialization.
2. The graphics cache path also refreshes rotation and transform matrices before cached projection work.
3. `calculate_transform_matrix` later consumes `cam->rotation_matrix` to build the full MVP-style transform used by projection code.
4. `apply_rotation_with_matrix` provides a direct vector helper for code paths that only need rotation and not the full transform matrix.

---

## Developer Notes
- This submodule only deals with rotation math and cached rotation state.
- It does not own camera input policy, map fitting, or transform-matrix projection assembly.
- The matrix composition order is explicit in `compose_rotation_matrix`: `rx * (ry * rz)`.
- The exported API for this folder is declared in `includes/render.h`.

For the higher-level camera controls that decide when these helpers should run, see the parent folder README in `../README.md`.