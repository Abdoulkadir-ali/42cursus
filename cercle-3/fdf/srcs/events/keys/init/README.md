# Key Init Module

Handles the keyboard dispatch entry points. This folder is responsible for routing raw key press and key release events into function-pointer tables.

---

## Directory Structure
- `srcs/events/keys/init/` — Key dispatch bootstrap
- `init.c` — Key press/release entry points
- `keys/` — Action-table population helpers

---

## How It Works

1. `key_press` looks up the pressed key in `key_actions`.
2. `key_release` looks up the released key in `key_releases`.
3. The chosen handler mutates event state and may request a redraw.

For exported declarations, see `includes/events.h`.