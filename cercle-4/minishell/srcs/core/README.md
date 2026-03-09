# Core Module

Handles shell startup, main loop, and signal setup. This subsystem is responsible for initializing the shell, managing the interactive prompt, and coordinating input, parsing, and execution.

---

## 📂 Directory Structure
- `srcs/core/` — Core logic root
  - `main.c` — Program entry point, shell initialization
  - `minishell.c` — Main interactive loop, prompt display, and command dispatch

---

## 🏗️ How It Works

### Global Pipeline
1. The process enters the program through `main` in `main.c`.
2. `main` immediately forwards control to `minishell(ac, av, envp)`.
3. `minishell` initializes the shell state and duplicates the inherited environment through `init_shell`.
4. It then checks whether execution should run in command-line mode through `handle_command_line_mode`.
5. If `-c` is active, one command string is executed directly and the shell exits with that status.
6. Otherwise `minishell` enters the main read-execute loop through `run_interactive_mode`.
7. The loop fetches one command line at a time with `get_command_line`.
8. Each line is handed to `process_input`, which drives parsing and the execution layer.
9. When input ends, `minishell` frees the duplicated environment with `cleanup_envp` and returns the final shell status.

### `main.c`
- Contains only the executable entry point.
- `main` forwards `ac`, `av`, and `envp` directly to `minishell`.
- No extra setup happens here; the real startup pipeline begins in `minishell.c`.

### `minishell.c`
- Owns shell startup, runtime mode selection, the main read loop, and final cleanup.
- Bridges the core module with the input, parsing, state, and exec subsystems.

#### Pipeline Inside `minishell.c`
1. `minishell` calls `init_shell(envp, &state.envp, &state)`.
2. If initialization fails, it returns `1` immediately.
3. It then calls `handle_command_line_mode(ac, av, &state)`.
4. `handle_command_line_mode` only activates when `ac >= 3` and `av[1]` matches `-c`.
5. In `-c` mode, it switches signals with `setup_signals(SIGNAL_HEREDOC)`, calls `process_input(av[2], state)`, clears readline history, and returns `state->exit_code`.
6. If `-c` mode is not active, `handle_command_line_mode` returns `-1` and `minishell` continues into `run_interactive_mode`.
7. `run_interactive_mode` switches to interactive signals through `setup_signals(SIGNAL_INTERACTIVE)` before the loop starts.
8. At the start of each iteration it clears `state->syntax_error`.
9. It then reads the next command line through `get_command_line(state)`.
10. If `get_command_line` returns `NULL`, the loop ends.
11. When EOF happens in an interactive shell, it prints `exit` to stderr before leaving the loop.
12. For a normal line, it calls `process_input(line, state)` and frees the line afterward.
13. After the loop, it clears readline history.
14. If the last processed input left `state->syntax_error` set, it returns `2`.
15. Otherwise it returns `state->exit_code`.
16. Back in `minishell`, `cleanup_envp(state.envp)` always runs before the final return.

#### Mode Split
- `-c` mode runs one command string from `av[2]` and exits.
- Interactive mode runs the prompt loop when stdin is a tty.
- The same loop also handles non-interactive stdin input because `get_command_line` delegates to the input subsystem, which can read from standard input without a prompt.

#### Runtime Handoff
1. `get_command_line` belongs to the input layer and decides how one line is read.
2. `process_input` drives tokenization, syntax validation, AST building, heredoc preparation, and execution.
3. Exit status is stored back into `state->exit_code`, which the core loop uses as the shell-visible result.
4. Syntax failures propagate through `state->syntax_error`, allowing the core loop to return `2` when the session ends after a syntax error.

---

## 🛠️ Developer Notes
- The core module is intentionally thin: it owns lifetime and control flow, while real line reading and execution are delegated to the input and exec modules.
- The final shell status comes from `state->exit_code`, except for the explicit syntax-error fallback to `2`.
- Environment duplication happens once at startup, and `cleanup_envp` releases that owned copy before exit.
- Readline history is cleared in both `-c` mode and loop mode to keep shutdown behavior consistent.

For detailed function documentation, see the source files and header definitions in `includes/core.h`.
