# Event Init Module

Handles creation of the event context and registration of runtime hooks. This folder is responsible for copying runtime pointers into `t_events`, initializing key and mouse state, and driving the per-frame loop hook.

---

## Directory Structure
- `srcs/events/init/` — Event bootstrap helpers
- `init.c` — Event object allocation and state initialization
- `hooks.c` — MLX hook registration
- `keys.c` — Key-state struct initialization
- `mouse.c` — Mouse-state struct initialization
- `loop.c` — Per-frame update loop

---

## How It Works

1. `init_events` allocates and fills the event context.
2. It seeds snapshot values from the graphics render config.
3. It initializes mouse and key state and installs the key dispatch tables.
4. `setup_hooks` binds the event callbacks to the window and MLX loop.
5. `loop_hook` updates FPS, smooth zoom, movement, rotation, and deferred graphics refreshes.

---

## Developer Notes
- The event context stores both direct subsystem pointers and a copy of the GUI struct.

For exported declarations, see `includes/events.h`.