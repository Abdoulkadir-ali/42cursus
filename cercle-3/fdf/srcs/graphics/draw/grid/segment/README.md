# Segment Module

Handles edge emission between neighboring grid points. This folder is responsible for computing neighbor coordinates, deciding whether to draw a standard segment, and inserting additional tessellated line segments when sub-unit LOD is active.

---

## Directory Structure
- `srcs/graphics/draw/grid/segment/` — Segment helpers
- `segment.c` — Standard segment emission
- `tessellation.c` — Intermediate point interpolation for dense segments
- `utils.c` — Neighbor and tessellation context setup

---

## How It Works

1. `compute_next_coords` resolves the horizontal or vertical neighbor.
2. `draw_segment` decides whether tessellation is needed.
3. `draw_tessellated_segment` interpolates additional points in map space, transforms them, and emits smaller line segments.
4. `draw_standard_segment` emits the direct cached line when visible.

---

## Developer Notes
- Tessellation is bounded to avoid exploding the number of generated line segments.

For exported declarations, see `includes/graphics.h`.