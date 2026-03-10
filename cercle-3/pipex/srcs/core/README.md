# Core Module

Handles program startup and argument dispatch. This folder owns the executable entry point and decides whether the runtime should execute the standard pipeline flow or the here-doc path.

---

## Directory Structure
- `srcs/core/` — Top-level application bootstrap
- `main.c` — Entry point, usage guard, and mode selection

---

## How It Works

1. `main` checks the raw CLI arguments.
2. It routes `here_doc` usage to the dedicated handler.
3. It rejects invalid argument counts with a usage message.
4. It normalizes the input before calling `pipex`.

---

## Developer Notes
- This folder should stay small and focused on launch-time decisions.

For exported declarations, see `includes/pipex.h`.