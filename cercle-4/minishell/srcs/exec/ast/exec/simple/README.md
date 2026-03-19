# exec/ast/exec/simple

Purpose
- Execute simple command AST nodes: handle dynamic expansion of arguments and
  assignments, detect builtins vs external binaries, and orchestrate child
  processes for external commands.

Overview
- `simple.c` is the high-level entry point:
  - `exec_simple_command()` expands `node->args` and `node->assigns` using the
    parsing expansion pipeline, handles empty expansions that only apply
    assignments, and then dispatches to runtime execution.
  - `run_with_expanded_args()` temporarily replaces the node's arrays with
    expanded versions, selects builtin vs external execution, restores state
    and frees temporary arrays.

- `builtins.c` contains helpers to run builtins while applying temporary
  assignment prefixes (`exec_builtin_with_assigns()`).

- `external.c` handles external command execution:
  - `exec_external_with_lookup()` resolves the executable via `PATH` and
    forks.
  - Child path (`child_execution`) configures child signals, applies
    assignments, updates `_` env, and `execve()`s the binary with proper
    errno-based exit codes.
  - Parent waits and normalizes the child's exit status.

Behavior notes
- Builtins run in-process and receive assignments applied to the current
  environment for their execution; assignments are restored afterwards.
- External binaries are executed in a forked child with `execve()`; common
  errno cases map to shell exit codes (127 for ENOENT, 126 for EACCES).

Usage
- Called by the executor when encountering simple command AST nodes. This
  layer depends on `expand_string_array()` to produce runtime arguments and
  assignment arrays.
