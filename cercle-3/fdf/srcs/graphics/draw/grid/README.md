# Grid Drawing Module

Handles traversal of the projected map surface. This folder is responsible for splitting the grid across threads, selecting between standard and horizon-aware traversal, and emitting either segments or triangle quads for each sampled cell.

---

## Directory Structure
- `srcs/graphics/draw/grid/` — Grid traversal root
- `threads.c` — Standard thread routines and joining
- `quad/` — Quad-to-triangle emission
- `raycast/` — Horizon-aware traversal and visibility clipping
- `segment/` — Neighbor segment drawing and optional tessellation

---

## How It Works

1. `draw_grid` selects threaded standard traversal or threaded raycast traversal.
2. Standard traversal walks rows and emits line segments or filled quads.
3. Raycast traversal expands outward from a peak region while respecting per-thread visible strips.
4. Segment and quad helpers convert neighboring cached points into line or triangle primitives.

---

## Developer Notes
- `lod_value` influences how densely rows and columns are sampled.
- The horizon-aware path is optimized for culling hidden geometry by screen column.

For exported declarations, see `includes/graphics.h`.