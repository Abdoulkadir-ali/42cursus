# Key Events Module

Handles keyboard dispatch and key-driven state changes. This folder is responsible for binding X11 keycodes to handler functions and splitting behavior between stateful flags, one-shot toggles, view changes, combo helpers, GUI actions, and map controls.

---

## Directory Structure
- `srcs/events/keys/` — Keyboard event root
- `init/` — Key press/release dispatch tables
- `handlers/` — Action handlers grouped by behavior

---

## How It Works

1. Key tables are initialized during event setup.
2. `key_press` and `key_release` look up handlers in the dispatch arrays.
3. Stateful keys update `events->keys` through the flag handlers.
4. One-shot handlers toggle rendering, camera, map, and GUI state directly.
5. The loop hook later consumes held movement and rotation flags.

---

## Developer Notes
- Handler folders are grouped by intent rather than by keycode range.

For exported declarations, see `includes/events.h`.