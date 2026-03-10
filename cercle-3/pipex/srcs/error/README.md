# Error Module

Handles lightweight error-reporting helpers. This folder is responsible for centralizing small shared exit paths so the rest of the runtime can fail consistently without repeating boilerplate.

---

## Directory Structure
- `srcs/error/` — Shared error helpers
- `exit.c` — `perror`-based return and process-exit utilities

---

## How It Works

1. `exit_statement` reports an error, frees a single owned pointer when needed, and returns a caller-chosen code.
2. `exit_process` prints the system error and terminates the current process with failure.

---

## Developer Notes
- Keep these helpers narrow; broader cleanup policy should remain with the caller.

For exported declarations, see `includes/pipex.h`.