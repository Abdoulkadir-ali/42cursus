# Quad Module

Handles conversion of one sampled grid cell into drawable primitives. This folder is responsible for collecting the four cached corner points of a cell and either drawing them as two triangles or falling back to line segments through the wider grid path.

---

## Directory Structure
- `srcs/graphics/draw/grid/quad/` — Quad emission helpers
- `quad.c` — Quad setup and per-row point processing

---

## How It Works

1. `draw_triangle_quad` loads the four projected corners for one cell.
2. It skips cells that are fully off screen.
3. `draw_quad_triangles` splits the quad into two triangles.
4. `draw_grid_row` walks a map row and delegates each sampled point to `process_grid_row_point`.

---

## Developer Notes
- The same row walker supports both wireframe and filled modes.

For exported declarations, see `includes/graphics.h`.