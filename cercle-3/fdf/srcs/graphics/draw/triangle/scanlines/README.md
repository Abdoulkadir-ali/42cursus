# Triangle Scanlines

Handles the inner loops for filled triangle rows. This folder is responsible for normalizing scanline bounds, preparing color and depth interpolation, clipping rows to the image, and writing the final pixels with or without z-buffer checks.

---

## Directory Structure
- `srcs/graphics/draw/triangle/scanlines/` — Scanline rasterization
- `dispatch.c` — Public scanline entry point
- `setup.c` — Scanline context setup and clipping
- `raster.c` — Fast versus depth-aware loop selection
- `fast.c` — Color-only scanline loops
- `depth.c` — Z-buffer-aware scanline loops
- `helper.c` — Swaps, pointer setup, and left/right clipping helpers
- `colors.c` — Fixed-point color conversion helpers

---

## How It Works

1. `draw_horizontal_scanline_z` normalizes left/right ordering and rejects invisible rows.
2. `init_scanline_ctx` prepares interpolation state and buffer pointers.
3. `draw_scanline_loop` selects the fast or depth-aware loop, and whether color shifting is active.
4. The chosen inner loop advances across the row and writes pixels.

---

## Developer Notes
- Scanlines use fixed-point color interpolation for stable per-pixel gradients.

For exported declarations, see `includes/graphics.h`.