# State Module

This module manages the shell's runtime state, including environment variables, shell level (SHLVL), and signal handling. It is essential for maintaining the shell's context and ensuring robust operation during user interaction and process execution.

## Directory Structure
- `env.c`: Handles environment variable management and manipulation.
- `shlvl.c`: Manages the shell level (SHLVL), tracking nested shell instances.
- `signals.c`: Sets up and manages signal handling for the shell (e.g., SIGINT, SIGQUIT).

## How It Works

### env.c
- Provides functions to initialize, update, and access environment variables.
- Ensures environment consistency across shell sessions and child processes.
- Typical operations: copying environment, updating variables, exporting, and unsetting.

### shlvl.c
- Manages the SHLVL environment variable, which tracks how many times the shell has been invoked recursively.
- On shell startup, increments SHLVL and updates the environment.
- Ensures correct SHLVL value for subshells and prevents overflow or invalid values.

### signals.c
- Sets up custom signal handlers for the shell.
- Handles signals like SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) to provide user-friendly behavior.
- Prevents shell from exiting unexpectedly and allows graceful interruption of running processes.

## Usage
- The state module is initialized at shell startup.
- It is used throughout the shell's lifecycle to maintain environment, shell level, and signal handling.
- Other modules interact with state functions to query or modify runtime context.

## Developer Notes
- Keep state initialization early in the shell startup sequence.
- Ensure signal handlers are robust and do not interfere with child process execution.
- Always update SHLVL correctly when spawning subshells.

---
For detailed function documentation, see the source files and header definitions in `includes/state.h`.