# Panel Module

Handles the GUI image buffer used for the left-side information panel. This folder is responsible for clearing stale pixels, painting the panel background, rebuilding the panel on resize, and triggering the section layout functions.

---

## Directory Structure
- `srcs/gui/panel/` — Panel image helpers
- `clear.c` — GUI image buffer clearing
- `draw.c` — Rectangle fill and panel background drawing
- `redraw.c` — Panel resize handling and layout orchestration

---

## How It Works

### Pipeline
1. `redraw_gui` receives the current event context.
2. `prepare_gui` checks whether the GUI image must be recreated for the current window height.
3. `clear_gui` zeroes the GUI image buffer.
4. `draw_panel_background` fills the panel and draws the accent border.
5. `render_gui_image` pushes the GUI image into the window.
6. `draw_gui_layouts` composes the controls, performance, projection, speed, map, and transform sections.

---

## Developer Notes
- Resize handling is height-driven because the panel width is fixed by `GUI_PANEL_WIDTH`.
- The background is drawn into the GUI image, while the text itself is written directly with MLX string calls.

For exported declarations, see `includes/gui.h`.