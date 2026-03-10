# Key Map Tables

Handles population of the key action and key release lookup tables. This folder is responsible for binding X11 key symbols to the appropriate event handlers.

---

## Directory Structure
- `srcs/events/keys/init/keys/` — Key mapping helpers
- `keys.c` — High-level action-table setup
- `actions.c` — Action table population in grouped batches
- `releases.c` — Release table population

---

## How It Works

1. `set_key_actions` populates the press table in five grouped passes.
2. `set_key_releases` assigns release handlers for stateful keys.
3. Key dispatch later resolves handlers through these tables in O(1) time.

For exported declarations, see `includes/events.h`.