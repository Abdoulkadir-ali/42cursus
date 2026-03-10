# Culling Stage

Handles coarse visibility tests, on-screen checks, backface rejection, and visible-map bound estimation. This stage is responsible for preventing unnecessary work before the drawing paths run.

---

## Directory Structure
- `srcs/render/stages/culling/` — Culling helpers
- `bounds.c` — Estimate the visible map subrange from projected sample points
- `culling.c` — On-screen tests, line rejection, and backface detection
- `visibility.c` — Whole-map visibility test and projection helper

---

## How It Works

### Global Pipeline
1. `render_scene` begins by calling `is_map_visible`.
2. `is_map_visible` refreshes the camera transform matrix.
3. It projects the eight corners of the map bounding box.
4. If the projected bounds do not overlap the window, the frame exits early.
5. If the map is visible and tessellation is active, `get_visible_map_bounds` estimates the active region on the base map.
6. During primitive drawing, `is_on_screen`, `should_draw_line`, and `is_backface` provide cheaper per-primitive rejection tests.

### `bounds.c`
- Samples the base map on a coarse stride and projects those points.
- Tracks the min and max map indices that still land on screen.
- Expands the discovered range with padding and clamps it back to the map size.
- Falls back to a small centered region if no coarse sample was visible.

### `culling.c`
- `is_on_screen` applies the current frustum margin around the window rectangle.
- `should_draw_line` rejects invalid or fully off-screen line segments.
- `is_backface` computes a 2D cross product to reject triangles facing away from the viewer.

### `visibility.c`
- `project_helper` normalizes raw map points before calling the transform stage.
- `compute_projected_bounds` builds a projected screen-space box from the eight corners of the height-field bounds.
- `is_map_visible` uses that projected box as the top-level render gate.

---

## Developer Notes
- `bounds.c` operates on `base_map` because tessellation decisions need the original map-space region.
- `visibility.c` uses `g->map` for z-range and dimensions during the frame visibility test.
- The culling stage mixes whole-map and per-primitive tests because both are needed at different costs and granularities.

For exported declarations, see `includes/render.h`.