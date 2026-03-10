# Performance Layout

Handles GUI sections related to render mode, optimization toggles, projection mode, point counts, and tessellation detail. This folder is responsible for surfacing the current render configuration to the user.

---

## Directory Structure
- `srcs/gui/layout/performance/` — Performance and render-state layout
- `performance.c` — Top-level optimization section composition
- `algorithm.c` — Render mode and filled-state display
- `optimizations.c` — Toggle state display
- `points.c` — Raw and active point statistics
- `projection.c` — Projection mode and alpha/FOV display
- `tesselation.c` — Detail level and target-point budget display

---

## How It Works

1. `draw_performance_display_layout` starts the optimization section.
2. It delegates point statistics, toggle state, algorithm description, and tessellation details to specialized helpers.
3. `draw_projection_display_layout` separately reports the active projection type and alpha/FOV value.
4. Point statistics derive active-point estimates from `detail_level` and `lod_value`.
5. Tessellation display formats the current detail level as TESS, LOD, or BASE.

---

## Developer Notes
- This folder is presentation-only: it reads render state but does not mutate it.
- The displayed values mirror fields inside `t_render_config` and `t_camera`.

For exported declarations, see `includes/gui.h`.