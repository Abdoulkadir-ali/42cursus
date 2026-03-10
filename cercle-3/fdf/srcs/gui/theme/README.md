# Theme Module

Handles GUI color palette selection. This folder is responsible for defining the available visual themes, resolving the active theme from the GUI style enum, and cycling styles at runtime.

---

## Directory Structure
- `srcs/gui/theme/` — GUI theme helpers
- `theme.c` — Theme palette constructors
- `utils.c` — Active-theme resolution and style cycling

---

## How It Works

1. Each constructor in `theme.c` returns one complete `t_gui_theme` palette.
2. `get_gui_theme` maps the current `t_gui_style` enum to the matching palette.
3. Rendering code reads the palette to color the panel background, accent border, and text.
4. `cycle_gui_style` advances to the next style and mirrors that change back into the camera state.

---

## Developer Notes
- Theme data is returned by value, so callers receive a full copy of the palette.
- GUI style is mirrored into the camera so controls and persisted state stay aligned.

For exported declarations, see `includes/gui.h`.