# Line Module

Handles projected line rasterization. This folder is responsible for preparing Bresenham stepping state, interpolating depth and color, selecting the proper rasterizer variant, and writing the line into the frame buffer.

---

## Directory Structure
- `srcs/graphics/draw/lines/` — Line drawing root
- `draw/` — High-level line setup and dispatch
- `bresenham/` — Standard and horizon-aware Bresenham implementations
- `helper.c` — Shared interpolation and pointer setup helpers

---

## How It Works

1. `draw_line` computes default clipping bounds from the window width.
2. `draw_line_clipped` initializes the draw context and Bresenham parameters.
3. Bresenham dispatch selects depth-aware, color-shifted, or horizon-aware stepping variants.
4. The chosen rasterizer advances through pixels and writes colors into the image.

---

## Developer Notes
- The line code operates on already-projected `t_point` values.
- Color interpolation uses fixed-point storage during Bresenham stepping.

For exported declarations, see `includes/graphics.h`.