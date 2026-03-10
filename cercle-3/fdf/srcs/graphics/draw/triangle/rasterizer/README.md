# Triangle Rasterizer

Handles edge-walking for flat-top and flat-bottom triangles. This folder is responsible for initializing the two active edges, clipping their Y range, producing scanline descriptors, and sending each scanline to the scanline renderer.

---

## Directory Structure
- `srcs/graphics/draw/triangle/rasterizer/` — Edge-walking helpers
- `rasterizer.c` — Public flat-top and flat-bottom entry points
- `helper.c` — Edge setup, clipping, scanline creation, and span stepping

---

## How It Works

1. Public rasterizer functions choose the correct edge pairing for the triangle shape.
2. Edge setup computes per-row deltas for position, depth, and color.
3. Y clipping advances the edges until they reach the visible image range.
4. Each row becomes one `t_scanline_data` payload sent to the scanline renderer.

---

## Developer Notes
- The rasterizer uses edge state in double precision but converts scanline values down to the scanline structs.

For exported declarations, see `includes/graphics.h`.