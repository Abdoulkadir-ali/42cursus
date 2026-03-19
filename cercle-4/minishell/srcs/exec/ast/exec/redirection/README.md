# exec/ast/exec/redirection

Purpose
- Implement execution semantics for redirection AST nodes: expand and validate
  redirection targets, open target files safely, temporarily swap file
  descriptors, execute the redirected branch and restore descriptors.

Overview
- `exec.c` contains the top-level flow for executing a redirection node:
  - `expand_and_validate_filename()` uses the parsing expansion helpers to
    expand the redirection target and rejects ambiguous results.
  - `open_expanded_filename()` opens the resolved filename according to the
    redirection type.
  - `perform_redirection_and_exec()` sets up descriptor substitution,
    executes the node's child subtree (`exec_tree`) and restores descriptors.

- `helper.c` provides lower-level utilities:
  - `is_valid_fd()` — validate numeric fd arguments.
  - `open_redirection_file()` — open according to redirection type and
    report errors (directories, open failures).
  - `get_target_fd()` — resolve which fd (stdin/stdout or a numeric fd) is
    being redirected.
  - `setup_redirection()` — `dup`/`dup2` helper that swaps descriptors and
    returns a saved copy to restore later.

Behavior notes
- Ambiguous redirects (expansion producing multiple filenames) produce an
  error and abort the redirection.
- Directory targets are rejected with an explicit message.
- Descriptor setup restores the original descriptor using `dup` and `dup2`
  even on nested redirections; callers must handle returned error codes.

Usage
- Called from the executor when visiting a redirection AST node. Matches the
  shell semantics of expanding the filename first, validating it, opening the
  file, and executing the redirection scope.
