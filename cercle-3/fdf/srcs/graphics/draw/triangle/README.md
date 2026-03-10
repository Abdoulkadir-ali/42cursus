# Triangle Module

Handles triangle emission and filling. This folder is responsible for choosing between wireframe and filled rendering, sorting triangle points into rasterizable forms, and converting triangle interiors into horizontal scanlines.

---

## Directory Structure
- `srcs/graphics/draw/triangle/` — Triangle drawing root
- `draw.c` — Public triangle and quad drawing entry points
- `helper.c` — Point swapping and edge stepping
- `rasterizer/` — Flat-top and flat-bottom rasterization helpers
- `scanlines/` — Horizontal scanline setup and draw loops

---

## How It Works

1. `draw_triangle` chooses wireframe or filled output.
2. Filled triangles are sorted by Y and split into flat-top or flat-bottom cases.
3. Rasterizer helpers walk the two active edges to generate scanlines.
4. Scanline helpers interpolate color and depth across each row.

---

## Developer Notes
- Filled mode also respects backface rejection when depth culling is active.

For exported declarations, see `includes/graphics.h`.