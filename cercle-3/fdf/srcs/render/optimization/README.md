# Render Optimization Module

Handles low-level draw-time optimizations shared by the graphics layer. This folder is responsible for depth-buffer tests and safe pixel writes into the main image buffer.

---

## Directory Structure
- `srcs/render/optimization/` — Render optimization helpers
- `lines.c` — Pixel write helper with depth-buffer integration
- `triangles.c` — Depth-buffer acceptance test used by line and triangle drawing paths

---

## How It Works

### Global Pipeline
1. Higher-level drawing code produces screen-space `t_point` values.
2. Before a pixel is written, `img_pixel_put_with_z` validates the graphics and image buffers.
3. It rounds the floating-point coordinates into integer screen coordinates.
4. It rejects pixels outside the image bounds.
5. It calls `z_buffer_test` to decide whether the new fragment is visible.
6. If the fragment passes, the target pixel address is computed inside the MLX image buffer.
7. The final color is stored as a packed integer.

### `lines.c`
- Contains `img_pixel_put_with_z`.
- Bridges projected points to the raw MLX framebuffer.
- Delegates depth ordering to `z_buffer_test`.

### `triangles.c`
- Contains `z_buffer_test`.
- Uses the window-owned depth buffer when `use_depth_culling` is enabled.
- Updates the stored depth when the new fragment is closer to the camera.

---

## Developer Notes
- The folder name is broader than the current implementation: at the moment it only owns z-aware pixel output helpers.
- `z_buffer_test` is shared infrastructure and is not limited to triangles despite the filename.
- The main image buffer comes from `window->main_img`, while the depth buffer lives in `window->z_buffer`.

For exported declarations, see `includes/graphics.h` and `includes/render.h`.