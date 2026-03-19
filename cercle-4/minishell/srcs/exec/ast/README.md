# AST Execution Pipeline

This directory contains the functions that execute the AST produced by the
parser. The layout below preserves the original section headings and summarizes
the executor responsibilities, dispatcher flow and error handling helpers used
across the runtime.

## Entry Point

`exec_tree` is the central dispatcher: it inspects the node type and routes to
the appropriate executor implementation (simple command, pipe, redirection,
logical operator, subshell, background task or semicolon sequencing).

Routing summary:

- `TOKEN_WORD` → `exec_simple_command`
- `TOKEN_PIPE` → `exec_pipe`
- redirections (`TOKEN_RED_IN`, `TOKEN_RED_OUT`, `TOKEN_APPEND`, `TOKEN_HEREDOC`) → `exec_redirection`
- `TOKEN_AND` / `TOKEN_OR` → `exec_logical` (`&&` / `||`)
- `TOKEN_SUBSHELL` → `exec_subshell`
- `TOKEN_BACKGROUND` → `exec_task`
- `TOKEN_SEMICOLON` → execute left then right sequentially

## Simple Command Path

`exec_simple_command` runs builtins in-process or external binaries in a
forked child. The executor first performs dynamic expansion of `node->args`
and `node->assigns`, applies temporary assignment prefixes when needed and
then dispatches to builtin or external execution. `find_path()` resolves
executables using `PATH` with directory rejection and access checks.

Key behaviors:

- Builtins: run in-process with temporary environment changes applied and
  restored afterwards.
- External: `fork()` + `execve()`; common errno values map to shell exit codes
  (127 for ENOENT, 126 for EACCES).

## Pipeline Path

Pipelines are executed by forking a left and a right child, wiring their
stdin/stdout to a `pipe()` pair, and waiting for both children. The reported
status of a pipeline is the normalized status of the rightmost command.

## Redirection Path

Redirections expand their target filename (rejecting ambiguous results), open
the file according to the redirection type, `dup`/`dup2` the descriptor into
place, execute the wrapped branch and restore the original descriptor.
Directory targets are rejected and reported as errors.

## Logical Operator Path

`exec_logical` implements short-circuit semantics for `&&` and `||` by
executing the right branch only when the left branch result satisfies the
operator condition.

## Subshell & Background Tasks

Subshells run in forked children with interactive behavior disabled in the
child. Background tasks fork and continue the parent execution without
waiting; the background child is put in its own process group.

## Wait Status Normalization

`handle_wait_status()` converts `waitpid()` results to POSIX shell-compatible
exit codes and prints appropriate diagnostics for signal terminations.

## Folder-Level Call Chain

1. `exec_tree`
2. `exec_simple_command` | `exec_pipe` | `exec_redirection` |
   `exec_logical` | `exec_subshell` | `exec_task`
3. recursive `exec_tree` calls for child subtrees
4. `handle_wait_status` for child termination normalization
