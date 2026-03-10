# Axis Layout

Handles the live axis indicator drawn in the window corner. This folder is responsible for rotating the canonical X, Y, and Z axes with the current camera matrix and labeling them on screen.

---

## Directory Structure
- `srcs/gui/layout/axis/` — Axis indicator helpers
- `drawing.c` — Axis line drawing
- `indicator.c` — Axis indicator orchestration
- `labels.c` — Axis label placement

---

## How It Works

1. `draw_axis_indicator` validates the GUI pointers and computes the indicator center.
2. It creates three canonical axis descriptors.
3. Each axis is rotated with `apply_rotation_with_matrix`.
4. `draw_axis_line` traces the rotated axis toward its endpoint with `mlx_pixel_put`.
5. `draw_axis_labels` writes the fixed X, Y, and Z labels around the indicator.

---

## Developer Notes
- The indicator is drawn directly to the MLX window, not into the GUI image.
- The axis length and margin are controlled by `AXIS_SIZE` and `AXIS_MARGIN`.

For exported declarations, see `includes/gui.h`.