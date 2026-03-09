# State Module

Handles shell runtime state: environment ownership, `SHLVL`, and signal mode
switching. This subsystem is responsible for turning inherited process state
into shell-owned state and keeping signal behavior consistent across the core,
execution, and heredoc paths.

---

## 📂 Directory Structure
- `srcs/state/` — Runtime state root
	- `env.c` — Environment duplication, state initialization, and env lookup
	- `shlvl.c` — `SHLVL` discovery, incrementing, and installation
	- `signals.c` — Signal mode switching for interactive, blocking, and heredoc states

---

## 🏗️ How It Works

### Global Pipeline
1. The core module calls `init_shell(envp, &state.envp, &state)` during startup.
2. `init_shell` duplicates the inherited environment into heap-owned storage.
3. It then updates or appends `SHLVL` through `add_shlvl_to_env`.
4. The initialized environment pointer is stored inside `state->envp`.
5. The module also records whether stdin is interactive and initializes runtime status fields such as `exit_code`, `syntax_error`, and `expansion_error`.
6. During shell execution, modules query variable values through `ft_get_env`.
7. Signal behavior is switched dynamically through `setup_signals` depending on whether the shell is waiting at the prompt, waiting on child processes, or reading a heredoc.

### `env.c`
- `duplicate_env_base` allocates the heap-owned environment copy used by the shell.
- `init_shell` is the public initialization entry point for `t_shell_state`.
- `ft_get_env` resolves the value of one variable inside a given environment array.

#### Pipeline Inside `env.c`
1. `init_shell` calls `duplicate_env_base(envp)`.
2. `duplicate_env_base` counts inherited entries, allocates a new array, and duplicates every string.
3. On allocation failure it frees any partially duplicated entries and returns `NULL`.
4. On success, `init_shell` calls `add_shlvl_to_env(*heap_env)`.
5. It then initializes `state->envp`, `state->interactive_shell`, `state->exit_code`, `state->syntax_error`, and `state->expansion_error`.
6. `ft_get_env` later provides read access by matching `KEY=` prefixes and returning a pointer to the value substring.

### `shlvl.c`
- `find_shlvl_index` locates an existing `SHLVL` entry.
- `calculate_shlvl` computes the next shell level.
- `make_shlvl_str` builds the serialized `SHLVL=<n>` string.
- `set_shlvl_entry` either replaces the existing entry or appends a new one.
- `add_shlvl_to_env` is the public entry point used during shell initialization.

#### Pipeline Inside `shlvl.c`
1. `add_shlvl_to_env` starts by calling `find_shlvl_index(heap_env)`.
2. If `SHLVL` already exists, it parses the current numeric value and passes it to `calculate_shlvl`.
3. If `SHLVL` does not exist, the new shell level defaults to `1`.
4. `calculate_shlvl` increments the inherited value and wraps back to `1` when the result would exceed `1000`.
5. `set_shlvl_entry` builds the replacement string through `make_shlvl_str`.
6. The new string is then either written into the existing slot or appended at the end of the environment array.

### `signals.c`
- `handle_interactive` implements Ctrl+C behavior while readline owns the terminal.
- `handle_heredoc` implements Ctrl+C behavior during heredoc reads.
- `setup_signal_mode` installs one concrete signal configuration.
- `setup_signals` is the public mode-switch entry point used by the rest of the shell.

#### Pipeline Inside `signals.c`
1. `setup_signals` receives one runtime mode.
2. For `SIGNAL_INTERACTIVE`, it installs `handle_interactive`.
3. For `SIGNAL_BLOCKING`, it installs `SIG_IGN` for `SIGINT` handling through `setup_signal_mode`.
4. For `SIGNAL_HEREDOC`, it installs `handle_heredoc`.
5. `setup_signal_mode` configures `SIGINT` with the requested handler, always ignores `SIGQUIT`, and clears `rl_event_hook`.
6. `handle_interactive` records `g_last_signal = 130`, prints a newline, and resets the current readline buffer when Ctrl+C is pressed.
7. `handle_heredoc` records the same signal status and prints a newline so the heredoc read path can stop cleanly.

---

## 🛠️ Developer Notes
- State initialization happens once at shell startup and produces the heap-owned environment that the rest of the shell mutates.
- `SHLVL` is normalized during initialization, so later modules can rely on `state->envp` already containing the updated value.
- `ft_get_env` returns pointers into the active environment array, so callers must treat the returned strings as borrowed data.
- Signal mode switching is intentionally centralized here so the core loop, external-command execution, and heredoc handling all share the same signal policy.
- `g_last_signal` is the bridge between asynchronous signal handlers and later control-flow decisions, such as mapping heredoc interruption to exit status `130`.

For detailed function documentation, see the source files and header definitions in `includes/state.h`.