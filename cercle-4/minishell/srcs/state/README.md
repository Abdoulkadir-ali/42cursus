# 🏷️ State Module

> **Manages shell runtime state: environment, SHLVL, and signals.**
>
Ensures robust operation and context management during shell execution.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Subsystem](https://img.shields.io/badge/Subsystem-State-blue?style=for-the-badge)

---

## 📖 Overview

The state module tracks environment variables, shell level (SHLVL), and signal handling. It is critical for maintaining shell context and safe process management.

---

## 📂 Layout
- `env.c` — environment variable management
- `shlvl.c` — shell level (SHLVL) tracking
- `signals.c` — signal setup and handling

---

## 🏗️ How It Works

### `env.c`
- Initializes, updates, and accesses environment variables
- Ensures environment consistency across sessions and child processes
- Typical operations: copy, update, export, unset

### `shlvl.c`
- Manages SHLVL environment variable (tracks shell recursion)
- Increments SHLVL on startup, updates environment
- Ensures correct SHLVL for subshells, prevents overflow/invalid values

### `signals.c`
- Sets up custom signal handlers (SIGINT, SIGQUIT)
- Handles Ctrl+C and Ctrl+\ gracefully
- Prevents unexpected shell exit, allows safe interruption

---

## 🛠️ Developer Notes
- Initialize state early in shell startup
- Signal handlers must not interfere with child processes
- Always update SHLVL correctly for subshells

For detailed function documentation, see the source files and header definitions in `includes/state.h`.
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