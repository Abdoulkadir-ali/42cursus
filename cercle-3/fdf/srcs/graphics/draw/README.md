# Draw Module

Handles primitive emission once the frame buffers and projection cache are ready. This folder is responsible for traversing the grid, dispatching line or triangle drawing, and performing the final pixel-level rasterization.

---

## Directory Structure
- `srcs/graphics/draw/` — Drawing root
- `grid/` — Surface traversal across the cached map grid
- `lines/` — Line setup and Bresenham rasterization
- `pixel/` — Final pixel writes with optional z-buffer updates
- `triangle/` — Triangle fill, edge walking, and scanline rasterization

---

## How It Works

1. Grid traversal chooses which neighboring cached points should form segments or quads.
2. Line drawing uses setup helpers to prepare Bresenham stepping and interpolation.
3. Triangle drawing either emits wireframe edges or fills the interior through scanlines.
4. Pixel helpers perform the last write into the MLX image.

---

## Developer Notes
- The draw layer assumes cached points are already in screen space.
- Filled and wireframe modes share traversal code but diverge in the primitive emitters.

For exported declarations, see `includes/graphics.h`.