# Bresenham Module

Handles the low-level line stepping loops. This folder is responsible for iterating across pixels, interpolating color and depth, supporting optional color shifting, and providing a horizon-aware variant for raycast rendering.

---

## Directory Structure
- `srcs/graphics/draw/lines/bresenham/` — Bresenham rasterizers
- `bresenham.c` — Backend dispatch
- `helper.c` — Shared stepping and interpolation helpers
- `standard.c` — Standard image-space line loops
- `raycast.c` — Horizon-aware line loops
- `helper.c` — Shared state preparation and stepping
- `raycast.c` — Raycast-specific horizon updates

---

## How It Works

1. The dispatcher examines depth and color-shift flags.
2. Standard loops draw directly into the image with optional z-buffer updates.
3. Raycast loops also update the horizon buffer and obey per-strip clipping bounds.
4. Shared stepping helpers update position, error terms, and interpolated color/depth values.

---

## Developer Notes
- Fixed-point color interpolation avoids repeated floating-point conversions inside the inner loop.

For exported declarations, see `includes/graphics.h`.