# Pixel Module

Handles the final image write for individual pixels. This folder is responsible for writing a color directly into the MLX image buffer, with or without z-buffer depth testing.

---

## Directory Structure
- `srcs/graphics/draw/pixel/` — Pixel write helpers
- `pixel.c` — Fast pixel writes with optional depth testing

---

## How It Works

1. Higher-level rasterizers prepare a `t_pixel_draw_params` payload.
2. `draw_pixel_fast_no_z` writes the color directly to the image.
3. `draw_pixel_fast` compares the incoming depth against the z-buffer before writing.

---

## Developer Notes
- This layer does not compute addresses; callers pass already-resolved pointers.

For exported declarations, see `includes/graphics.h`.