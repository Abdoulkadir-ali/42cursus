# Core Module

Handles shell startup, main loop, and signal setup. This subsystem is responsible for initializing the shell, managing the interactive prompt, and coordinating input, parsing, and execution.

---

## 📂 Directory Structure
- `srcs/core/` — Core logic root
  - `main.c` — Program entry point, shell initialization
  - `minishell.c` — Main interactive loop, prompt display, and command dispatch

---

## 🏗️ How It Works

### `main.c`
- Initializes shell state, environment, and signal handlers.
- Sets up the main loop and prepares resources.
- Entry point for the executable (`int main(int argc, char **argv, char **envp)`).

### `minishell.c`
- Implements the main interactive loop.
- Displays prompt, reads user input, and dispatches commands.
- Coordinates input, parsing, and execution modules.
- Handles shell exit and cleanup.

#### Typical Flow
1. Shell is initialized in `main.c`.
2. Main loop in `minishell.c` displays prompt and reads input.
3. Input is passed to parsing and execution modules.
4. Shell handles signals, errors, and exits gracefully.

---

## 🛠️ Developer Notes
- Initialization is robust to handle environment and signal setup.
- Main loop is modular, allowing easy integration of input, parsing, and execution.
- Cleanup routines ensure safe resource management on exit.

For detailed function documentation, see the source files and header definitions in `includes/core.h`.
