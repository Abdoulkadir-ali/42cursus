# Graphics Init Module

Handles graphics-state allocation and default configuration. This folder is responsible for building the `t_graphics` object, preparing render settings, zeroing frame timing state, and allocating the horizon buffer.

---

## Directory Structure
- `srcs/graphics/init/` — Graphics initialization helpers
- `init.c` — Render config, frame data, and graphics allocation

---

## How It Works

1. `init_render_config` seeds the default render options.
2. `init_frame_data` resets the frame timing counters.
3. `init_graphics` allocates the graphics object, clears map and cache fields, allocates the horizon buffer, and stores default config/data.

---

## Developer Notes
- `init_graphics` keeps both the base map and the active map pointer so later LOD and tessellation logic can swap maps safely.

For exported declarations, see `includes/graphics.h`.