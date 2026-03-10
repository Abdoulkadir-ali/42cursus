# Projection Stage

Handles projection-matrix construction, camera transform-matrix assembly, and conversion of map-space points into screen-space points. This stage is responsible for all matrix-driven point transformation used by culling, cache generation, and drawing.

---

## Directory Structure
- `srcs/render/stages/projections/` — Projection helpers
- `matrix.c` — Parallel and conic projection matrix builders
- `transform.c` — Per-point transform application
- `view.c` — View and final transform-matrix assembly
- `scanlines/` — Row-based transform helpers for projection caches

---

## How It Works

### Global Pipeline
1. Camera setup and visibility tests refresh `cam->transform_matrix` through `calculate_transform_matrix`.
2. `calculate_transform_matrix` builds the rotation, view, projection, and screen-scale matrices.
3. The final product is stored in `cam->transform_matrix`.
4. `apply_transform` uses that cached matrix to convert a point into screen space.
5. Culling helpers call `apply_transform` through `project_helper`.
6. Cache builders can transform whole rows through `transform_scanline` in the nested `scanlines/` subfolder.

### `matrix.c`
- Builds the projection matrix for the current camera mode.
- `get_projection_matrix` chooses between parallel and conic projection.
- The parallel path can add an oblique-style skew when `alpha` differs from `90` degrees.
- The conic path clamps FOV and builds a perspective-style matrix.

### `transform.c`
- Pre-adjusts the point around the camera grid center and z-scale.
- Multiplies the adjusted vector by the cached transform matrix.
- Applies the camera screen offset.
- Recomputes depth in camera-facing space from the cached rotation matrix and `view_dist`.

### `view.c`
- Converts the cached 3x3 camera rotation into a 4x4 rotation matrix.
- Builds the view matrix with a camera-distance translation.
- Builds the projection matrix.
- Applies an additional screen-space scale factor derived from projection mode and camera scale.
- Stores the final matrix back into `cam->transform_matrix`.

---

## Developer Notes
- The projection stage consumes the cached camera rotation matrix built by the camera rotate submodule.
- `view_dist` is computed here and later reused by the transform stage when writing depth.
- The aspect ratio is currently passed as `1.0f` in this code path, so the screen-scale stage carries most of the visible sizing behavior.

For exported declarations, see `includes/render.h`.