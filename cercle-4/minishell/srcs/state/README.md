# State: environment and runtime helpers

This directory holds small, focused helpers that make the shell's runtime
environment predictable and safe to use across the core, parsing, and
execution subsystems.

The responsibilities here are intentionally minimal:

- provide a heap-owned copy of the inherited environment for the shell to
	modify and query (`env.c`),
- normalize and manage `SHLVL` on startup (`shlvl.c`), and
- centralize signal-mode switching for the running shell (see the
	`signals/` subdirectory for details).

---

## Files

- `env.c` — duplicate the inherited `envp` into a heap-owned array, expose
	`init_shell()` and `ft_get_env()` for callers to initialize and read the
	active environment.
- `shlvl.c` — compute and install the `SHLVL` entry used by interactive
	shells; `add_shlvl_to_env()` is called during initialization.
- `signals/` — subdirectory that implements the signal handlers and the
	`setup_signals()` API. See `srcs/state/signals/README.md` for details.

---

## Quick overview

- `init_shell(char **envp, char ***out_envp, t_shell_state *state)` duplicates
	the provided `envp` into a heap-owned array and writes it to `*out_envp`.
	It also initializes fields inside `state` such as `exit_code` and
	`interactive_shell`.
- `ft_get_env(char **envp, const char *key)` performs a simple `KEY=` prefix
	lookup and returns the value substring or `NULL`.
- `add_shlvl_to_env(char **heap_env)` locates or appends `SHLVL=` and writes
	an appropriate numeric value (defaults to `1`, wraps large values per
	POSIX-style behavior implemented in `calculate_shlvl`).

---

## Developer notes

- The environment copy returned by `init_shell` is owned by the shell and
	may be mutated; callers should treat returned strings from `ft_get_env`
	as borrowed pointers into that array.
- `add_shlvl_to_env` intentionally keeps allocation and replacement logic
	simple: it builds a single `SHLVL=<n>` string and either replaces the
	existing slot or appends it.
- Signal-mode switching is implemented in a dedicated subdirectory so signal
	logic can be kept independent and testable; call `setup_signals()` rather
	than installing handlers directly.

For implementation details, see `env.c`, `shlvl.c`, and
`srcs/state/signals/README.md`.