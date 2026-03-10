# Line Setup Module

Handles the high-level setup for line rasterization. This folder is responsible for collecting screen coordinates, buffer pointers, interpolation state, clipping bounds, and the dispatch flags used by the Bresenham backends.

---

## Directory Structure
- `srcs/graphics/draw/lines/draw/` — Line setup helpers
- `draw.c` — Public line entry points
- `line_setup.c` — Screen-space setup and pointer resolution

---

## How It Works

1. `init_draw_line_ctx` converts `t_point` endpoints into integer screen-space positions.
2. It resolves image and z-buffer pointers and prepares interpolation data.
3. `draw_line_clipped` fills the Bresenham parameter struct and dispatches to the proper backend.

---

## Developer Notes
- Visibility rejection happens early if the start point falls outside the target image.

For exported declarations, see `includes/graphics.h`.