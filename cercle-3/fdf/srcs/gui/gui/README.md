# GUI Core

Handles GUI object allocation and the top-level redraw bridge between the event layer, the renderer, and the panel system.

---

## Directory Structure
- `srcs/gui/gui/` — GUI core helpers
- `init.c` — GUI object and GUI image allocation
- `redraw.c` — Per-frame GUI redraw orchestration

---

## How It Works

### Pipeline
1. `init_gui` allocates one `t_gui` structure.
2. It binds shared pointers to the window, camera, map manager, render config, and active map.
3. It copies the camera style into `gui_style`.
4. It allocates the GUI image through `init_gui_images`.
5. During frame redraw, `redraw` copies event-owned render flags back into the graphics context.
6. It calls `render_scene`.
7. It pushes the main and GUI images to the window.
8. It updates the GUI FPS value from frame timing data.
9. It calls `redraw_gui(events)` and `draw_axis_indicator(&events->gui)`.

---

## Developer Notes
- `redraw` is the bridge where event state becomes render state.
- The GUI image lives inside `window->gui_img`, not inside `t_gui` itself.
- Axis drawing happens after panel redraw so the overlay reflects the current camera orientation.

For exported declarations, see `includes/gui.h`.