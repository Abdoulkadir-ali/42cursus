# GUI Module

Handles the on-screen interface layered on top of the rendered scene. This subtree is responsible for allocating the GUI image, composing the information panels, formatting textual values, and drawing small direct-to-window overlays such as the axis indicator.

---

## Directory Structure
- `srcs/gui/` — GUI root
- `gui/` — GUI object initialization and frame redraw bridge
- `layout/` — Information layout sections and presentation helpers
- `panel/` — Panel image clearing, background drawing, and GUI image redraw
- `print/` — Text output and lightweight formatting helpers
- `theme/` — Theme selection and GUI style cycling

---

## How It Works

### Global Pipeline
1. Core startup creates the GUI state through `init_gui`.
2. `init_gui` stores the shared window, camera, map, and render configuration pointers.
3. It allocates the GUI image through `init_gui_images`.
4. During each frame, `redraw` first renders the 3D scene.
5. It then pushes the main image and GUI image to the MLX window.
6. `redraw_gui` clears the GUI image, redraws the panel background, and composes the panel sections.
7. Print helpers emit colored MLX text for keys, labels, and values.
8. Theme helpers supply the active colors for the panel background and accents.
9. `draw_axis_indicator` draws the live axis overlay directly to the window.

---

## Developer Notes
- The GUI uses both image-based drawing and direct MLX window drawing.
- Layout helpers are split by information category so the panel can be recomposed section by section.
- Numeric formatting is intentionally lightweight and avoids `printf` inside the hot redraw path.
- Theme selection is camera-style driven through `gui_style`.

For exported declarations, see `includes/gui.h`.