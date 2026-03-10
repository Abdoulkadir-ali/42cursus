# Key Handlers

Handles all key-driven behavior after dispatch. This folder is responsible for grouping actions into state flags, combos, GUI exit, render toggles, view changes, and map operations.

---

## Directory Structure
- `flags/` — Stateful key press/release flags and modifier helpers
- `combos/` — Plus/minus/zero combo handlers
- `gui/` — GUI-related key actions such as exit
- `toggle/` — Render and camera toggle handlers
- `view/` — Movement, projection, rotation, and alignment controls
- `map/` — Map cycling, generation, style, and GUI-style changes

---

## Developer Notes
- Stateful handlers usually return `0` because the visible change is processed later from the loop hook.
- One-shot handlers usually return `1` to request an immediate redraw.

For exported declarations, see `includes/events.h`.