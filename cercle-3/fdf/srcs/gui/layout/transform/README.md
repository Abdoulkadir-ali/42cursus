# Transform Layout

Handles FPS and transform-stat display for the current camera. This folder is responsible for showing current offsets, rotation angles, and scale in a compact stats panel.

---

## Directory Structure
- `srcs/gui/layout/transform/` — Runtime transform stats
- `transform.c` — Top-level stats composition
- `fps.c` — FPS display
- `movement.c` — Move, zoom, and rotation speed display
- `pos.c` — Camera offset display
- `rot.c` — Camera rotation angle display
- `scale.c` — Camera scale display
- `utils.c` — Angle normalization helper

---

## How It Works

1. `draw_transform_stats` creates a compact layout near the right side of the window.
2. It displays an FPS section first.
3. It then emits transform rows for offset, rotation, and scale.
4. `display_rot_stats` normalizes the raw camera rotation values into degrees through `normalize_angle`.
5. `draw_speed_display_layout` separately reports movement, zoom, and rotation-speed multipliers.

---

## Developer Notes
- This folder is read-only with respect to runtime state.
- Rotation display converts radians to wrapped degree values for readability.

For exported declarations, see `includes/gui.h`.