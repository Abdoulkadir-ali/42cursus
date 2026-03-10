# Projection Scanlines Submodule

Handles row-based projection helpers used when transforming many map points into screen space. This submodule is responsible for applying the cached camera transform across one contiguous row of map data.

---

## Directory Structure
- `srcs/render/stages/projections/scanlines/` — Scanline projection helpers
- `scanline.c` — Transform one map row into projected `t_point` values

---

## How It Works

### Global Pipeline
1. A caller provides an output point buffer, a row start index, and the row width.
2. `transform_scanline` walks that row in order.
3. Valid map points are loaded from `g->map->points`.
4. Each valid point is transformed through `apply_transform`.
5. Invalid source points are marked with `BAD_VALUE` in the output buffer.

### `scanline.c`
- Implements a straight row loop with no internal allocation.
- Uses the active `g->map` rather than `base_map`, so it works with tessellated maps as well.
- Preserves per-point colors from the source map.

---

## Developer Notes
- This helper is designed for batch-friendly projection work.
- It assumes the caller has already prepared the camera transform matrix for the current frame.
- The output buffer is indexed with the same flat row-major indexing scheme as the source point arrays.

For exported declarations, see `includes/render.h`.