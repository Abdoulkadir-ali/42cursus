# Titles Layout

Handles the controls guide and reusable title-oriented section helpers. This folder is responsible for rendering static instructional text and combo summaries inside the GUI panel.

---

## Directory Structure
- `srcs/gui/layout/titles/` — Controls and title helpers
- `draw.c` — Full controls-guide composition
- `helper.c` — Combo value formatting helper
- `section.c` — Rotation, mouse, keyboard, combo, and optimization subsections

---

## How It Works

1. `draw_controls_guide_layout` composes the controls panel from smaller sections.
2. It adds rotation instructions, mouse controls, keyboard controls, combo summaries, and optimization hints in order.
3. `draw_combo_value` joins a prefix with a formatted runtime value before emitting it as a key/value row.
4. The section helpers provide the static labels and the combo section reads live camera and map values.

---

## Developer Notes
- This folder mixes static help text and a small amount of live value formatting.
- The combo section depends on `camera->alpha`, `camera->rotation_speed`, and `map->z_divisor`.

For exported declarations, see `includes/gui.h`.