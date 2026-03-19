# Signals Submodule

This directory implements the shell's signal policy and the small helpers used
to adapt signal delivery to the three runtime modes the shell requires:

- interactive prompt (readline owns the terminal)
- blocking waits for child processes
- heredoc reading (blocking, but needs a different SIGINT behavior)

---

## Files
- `handlers.c` — concrete signal handlers and the `setup_signal_mode` helper.
- `signals.c` — public signal-mode switching API and `g_last_signal` global.

---

## Purpose and API

The signals submodule centralizes signal behavior so callers can switch modes
without duplicating installation logic.

- `void setup_signals(int mode)` — install the requested runtime signal
	configuration. Valid `mode` values are defined in `includes/state.h`.
- `void setup_child_signals(void)` — reset child processes to the default
	handlers (`SIG_DFL`) for `SIGINT`, `SIGQUIT`, and `SIGTERM`.

Handlers implemented in `handlers.c`:

- `handle_interactive(int sig)` — used while readline is active. Sets
	`g_last_signal = 130` for `SIGINT`, prints a newline and resets the current
	readline buffer so the prompt appears on a fresh line.
- `handle_heredoc(int sig)` — used while reading heredoc input. Records the
	`SIGINT` delivery (also `130`) and writes a newline so the read loop can
	terminate cleanly.
- `handle_sigterm(int sig)` — records `SIGTERM` in `g_last_signal`.
- `int event_hook(void)` — a small `readline` event hook that will set
	`rl_done = 1` when a `SIGTERM` has been received.

`g_last_signal` is the bridge between asynchronous handlers and synchronous
control-flow: callers read it to map interruptions to exit codes or to stop
blocking reads.

---

## Usage notes

- Call `setup_signals(SIGNAL_INTERACTIVE)` when entering the prompt loop so
	`Ctrl+C` resets the input line and returns control to the main loop.
- Call `setup_signals(SIGNAL_BLOCKING)` before waiting on child processes to
	ignore `SIGINT` (children will receive the signal instead).
- Call `setup_signals(SIGNAL_HEREDOC)` while performing heredoc reads so a
	single `Ctrl+C` interrupts the heredoc without affecting the parent prompt
	state.
- In executed child processes, call `setup_child_signals()` to restore default
	behavior before `execve`.

---

## Developer notes

- `handlers.c` uses `readline` hooks (`rl_on_new_line`, `rl_replace_line`,
	`rl_redisplay`, and `rl_event_hook`) — the code depends on linking with
	readline and on those symbols being visible.
- The handlers set `g_last_signal` to a small set of sentinel values (`130`
	for `SIGINT`, `SIGTERM` for termination) so higher-level code can decide
	the proper exit status.
- Keep signal installation centralized here; other modules should call the
	public `setup_signals` entry points rather than installing handlers
	themselves.

For concrete behavior and implementation details, see `handlers.c` and
`signals.c` in this directory and the public declarations in
`includes/state.h`.