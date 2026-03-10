# Graphics Module

Handles the low-level drawing side of the renderer. This subtree is responsible for graphics state allocation, frame buffer clearing, projection caching, threaded grid traversal, line and triangle rasterization, and the final pixel writes into the MLX image.

---

## Directory Structure
- `srcs/graphics/` — Graphics root
- `cache/` — Projected-point cache allocation and reuse
- `draw/` — Grid, line, triangle, and pixel drawing
- `frames/` — Frame buffer clearing
- `init/` — Graphics-state initialization

---

## How It Works

### Global Pipeline
1. `init_graphics` allocates the `t_graphics` state, render configuration, frame timing data, and horizon buffer.
2. At frame time, `clear_frame_buffers` resets the main image and optional z-buffer.
3. `cache_projections` updates the camera matrices, allocates the projection cache if needed, and precomputes transformed points.
4. `draw_grid` selects the standard threaded grid pass or the horizon-aware raycast pass.
5. Grid traversal turns cached map points into line segments or triangle quads.
6. Line and triangle helpers rasterize primitives into scanlines and pixels.
7. Pixel helpers write the final colors into the MLX image, optionally updating the z-buffer.

---

## Developer Notes
- This module is the lowest rendering layer; it expects camera, map, and transform work to already be prepared.
- The projection cache exists to avoid repeating expensive transforms during line and triangle traversal.
- Horizon culling uses a separate path that clamps work per screen column.

For exported declarations, see `includes/graphics.h`.