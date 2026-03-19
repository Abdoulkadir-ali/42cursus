# exec/ast/exec

Purpose
- Executor for AST nodes: implements runtime behavior for assignments,
  redirections, simple commands, pipelines, logical operators, background
  tasks and process waiting/normalization.

Overview
- Files in this directory implement the core execution primitives used by the
  AST walker (`exec_tree()`):
  - `assignment.c` — save/duplicate environment, apply temporary assignment
    prefixes to `state->envp`, and restore the original environment.
  - `expand.c` — adapter helpers that run the parsing expansion pipeline
    (`expand_tokens`) and convert token lists into `char **` arrays used by
    command execution and redirections.
  - `logical.c` — subshell execution and logical operator handling
    (`exec_logical` for `&&`/`||` semantics and `exec_subshell`).
  - `path.c` — `find_path()` and helpers to resolve an executable candidate
    from `PATH`, with directory rejection and access checks.
  - `pipe.c` — two-child pipeline implementation: fork left/right, connect
    with `pipe()`, and return rightmost command status.
  - `task.c` — background job handling (fork and continue without waiting).
  - `wait.c` — normalize `waitpid()` statuses into shell exit codes
    (`handle_wait_status`).

Behavior notes
- Assignment prefixes are applied by duplicating `state->envp` so builtins and
  child processes can observe temporary environment changes; the original
  environment is restored after execution.
- Expansion helpers in `expand.c` are thin adapters around parsing-level
  expansion; redirection expansion must produce exactly one filename or the
  executor reports an ambiguous redirect.
- Pipelines and subshells are implemented with protected forks and careful
  signal mode changes to match interactive shell behavior.

Usage
- The executor (`exec_tree`) calls these functions when traversing AST nodes.
  Review individual files for exact error codes and edge-case handling.
