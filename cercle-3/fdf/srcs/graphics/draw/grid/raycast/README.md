# Raycast Grid Module

Handles the horizon-culling traversal path. This folder is responsible for partitioning the screen into visible strips, scanning outward from a peak area, clipping primitive emission to strip bounds, and updating the horizon buffer during line drawing.

---

## Directory Structure
- `srcs/graphics/draw/grid/raycast/` — Horizon-aware grid traversal
- `grid.c` — Top-level grid dispatch and section iteration
- `raycast.c` — Outward surface scan from the peak indices
- `threads.c` — Per-strip threaded dispatch
- `primitive.c` — Strip-clipped primitive emission
- `helper.c` — Horizon-buffer pixel helpers for Bresenham
- `utils.c` — Cached-point and peak-selection helpers
- `visibility.c` — Lightweight visibility gate

---

## How It Works

1. `draw_grid_raycast_threaded` splits the window width into visible strips.
2. Each thread locates a peak sample and scans outward in four quadrants.
3. `draw_surface_primitive` fetches the needed cached neighbors and emits lines or triangles.
4. Raycast-specific Bresenham helpers update the horizon buffer so later pixels behind the horizon are skipped.

---

## Developer Notes
- Strip clipping keeps each worker confined to a horizontal screen range.
- The peak heuristic samples a small 3x3 set of map positions to anchor traversal.

For exported declarations, see `includes/graphics.h`.