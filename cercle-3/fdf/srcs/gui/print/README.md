# Print Module

Handles low-level GUI text output and compact numeric formatting. This folder is responsible for drawing colored text rows in the window and converting runtime values into short display strings.

---

## Directory Structure
- `srcs/gui/print/` — GUI text output helpers
- `put.c` — Text, key, value, and arbitrary-color drawing helpers
- `format/` — Numeric string formatting helpers

---

## How It Works

1. Layout code decides what to display and where to place it.
2. Format helpers convert speeds, floats, and counters into stack buffers.
3. `put_text`, `put_key`, `put_value`, and `put_colored` send the final strings to MLX with the appropriate color.

---

## Developer Notes
- This module keeps formatting simple to avoid heavier formatting code inside the redraw path.
- All drawing in this folder targets the active window through `mlx_string_put`.

For exported declarations, see `includes/gui.h`.