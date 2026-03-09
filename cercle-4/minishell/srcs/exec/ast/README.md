# AST Execution Pipeline

This directory contains the functions that execute the AST produced by parsing.
The flow below is function-oriented and follows the exact calls inside this folder.

## Entry Point

`exec_tree` in `tree.c` is the dispatcher for every AST node.

Its routing is exact:

- `TOKEN_WORD` -> `exec_simple_command`
- `TOKEN_PIPE` -> `exec_pipe`
- `TOKEN_RED_IN`, `TOKEN_RED_OUT`, `TOKEN_APPEND`, `TOKEN_HEREDOC` -> `exec_redirection`
- `TOKEN_AND` -> `exec_logical(..., 1)`
- `TOKEN_OR` -> `exec_logical(..., 0)`
- `TOKEN_SUBSHELL` -> `exec_subshell`
- `TOKEN_SEMICOLON` -> `exec_tree(left)` then `exec_tree(right)`

## Simple Command Path

`exec_simple_command` in `simple.c` handles one command node.

The steps are:

1. If `node->args` or `node->args[0]` is missing, it returns `0`.
2. If `is_builtin(node->args[0], node->args)` is true, it calls `exec_builtin(node->args, state)` and returns that status.
3. Otherwise it calls `find_path(node->args[0], state)`.
4. If `find_path` fails:
   - when the command contains `/`, it reports `No such file or directory` and returns `127`
   - otherwise it reports `command not found` and returns `127`
5. If `find_path` succeeds, it calls `run_external_command`.

`find_path` in `path.c` resolves the executable path.

The steps are:

1. Reject a null or empty command.
2. If the command already contains `/`:
   - return `ft_strdup(cmd)` when the path exists
   - return `NULL` otherwise
3. Read `PATH` from `state->envp` with `ft_get_env("PATH", state->envp)`.
4. If `PATH` is missing, use `/bin:/usr/bin:/usr/local/bin`.
5. If `PATH` is empty, return `NULL`.
6. Call `find_executable_in_paths`.
7. Pass the result through `validate_and_return` so directories are rejected.

`find_executable_in_paths` scans the PATH list one entry at a time.

For each entry it:

1. Extracts one directory between `:` separators.
2. Calls `try_path(dir, cmd)`.
3. Returns immediately on the first hit.

`try_path` builds `dir + "/" + cmd`, then returns that string only when:

- `access(full_path, X_OK) == 0`
- `stat(full_path, &st) == 0`
- `full_path` is not a directory

`run_external_command` executes the resolved path.

The steps are:

1. `fork()` one child.
2. In the child, call `child_execution(path, node, state)`.
3. In the parent, switch to blocking signal mode.
4. `waitpid(pid, &status, 0)`.
5. Restore interactive signal mode.
6. Free the allocated `path`.
7. Return `handle_wait_status(status)`.

`child_execution` performs the `execve` call.

The steps are:

1. Reset `SIGQUIT` to `SIG_DFL`.
2. Update `_` in the environment with `ft_set_env("_", path, state)`.
3. Call `execve(path, node->args, state->envp)`.
4. If `execve` fails:
   - `ENOENT` -> print `No such file or directory`, `exit(127)`
   - `EACCES` on a directory -> print `Is a directory`, `exit(126)`
   - `EACCES` otherwise -> print `Permission denied`, `exit(126)`
   - any other error -> print `perror`, `exit(1)`

## Pipeline Path

`exec_pipe` in `pipe.c` executes a binary pipeline node.

The steps are:

1. Create a pipe with `pipe(pipefd)`.
2. Call `fork_left_command(pipefd, node, state)`.
3. Call `fork_right_command(pipefd, node, state)`.
4. Close both pipe descriptors in the parent.
5. Call `wait_for_children(pid1, pid2)`.

`fork_left_command` does the left branch setup.

The child path is:

1. Close `pipefd[0]`.
2. `dup2(pipefd[1], STDOUT_FILENO)`.
3. Close `pipefd[1]`.
4. `exit(exec_tree(node->left, state))`.

`fork_right_command` does the right branch setup.

The child path is:

1. Close `pipefd[1]`.
2. `dup2(pipefd[0], STDIN_FILENO)`.
3. Close `pipefd[0]`.
4. `exit(exec_tree(node->right, state))`.

`wait_for_children` waits for both children and returns the status of the second `waitpid`, which is the right side of the pipeline.

That means the pipeline status comes from the rightmost command.

## Redirection Path

`exec_redirection` in `redirection.c` wraps execution of `node->left` with one descriptor replacement.

The steps are:

1. Call `get_target_fd(node)`.
2. Call `open_redirection_file(node, &fd)`.
3. Call `setup_redirection(target_fd, fd, &save_fd)`.
4. Execute the wrapped branch with `exec_tree(node->left, state)`.
5. Restore the original descriptor with `dup2(save_fd, target_fd)`.
6. Close `save_fd`.
7. Return the wrapped branch status.

`get_target_fd` decides which descriptor to replace.

The rules are:

- default is `STDOUT_FILENO`
- `TOKEN_RED_IN` and `TOKEN_HEREDOC` switch the default to `STDIN_FILENO`
- if `node->args[1]` starts with a digit, `is_valid_fd` must accept it, then `ft_atoi(node->args[1])` becomes the target fd

`is_valid_fd` accepts only strings that:

- are not null and not empty
- are fully consumed by `strtol`
- produce a value in `[0, INT_MAX]`

`open_redirection_file` opens the file named in `node->args[0]`.

The exact mapping is:

- `TOKEN_RED_IN` -> `open(..., O_RDONLY)`
- `TOKEN_RED_OUT` -> `open(..., O_WRONLY | O_CREAT | O_TRUNC, 0644)`
- `TOKEN_APPEND` -> `open(..., O_WRONLY | O_CREAT | O_APPEND, 0644)`
- any other case in this file, including heredoc-backed input -> `open(..., O_RDONLY)`

It rejects directory targets before opening and prints the related system error when `open` fails.

`setup_redirection` saves the current descriptor with `dup(target_fd)`, then installs the new one with `dup2(fd, target_fd)`.

## Logical Operator Path

`exec_logical` in `control.c` handles both `&&` and `||`.

The steps are:

1. Execute the left branch with `exec_tree(node->left, state)`.
2. For `&&`, execute the right branch only when the left status is `0`.
3. For `||`, execute the right branch only when the left status is not `0`.
4. Return either the right branch status when it ran, or the left branch status otherwise.

## Subshell Path

`exec_subshell` in `control.c` handles `TOKEN_SUBSHELL` nodes.

The steps are:

1. `fork()` one child.
2. In the child, call `exec_subshell_child(node, state)`.
3. In the parent, call `exec_subshell_parent(pid)`.

`exec_subshell_child` does the isolated execution.

The steps are:

1. Reset `SIGQUIT` to default.
2. Force `state->interactive_shell = 0`.
3. Execute the subshell body with `exec_tree(node->left, state)`.
4. `exit(status)`.

`exec_subshell_parent` waits for the child, restores interactive signals, and returns `handle_wait_status(status)`.

## Wait Status Normalization

`handle_wait_status` in `wait.c` translates raw `waitpid` data into shell statuses.

The exact rules are:

- if `WIFEXITED(status)` -> return `WEXITSTATUS(status)`
- if `WIFSIGNALED(status)`:
  - `SIGINT` -> write a newline and return `130`
  - `SIGQUIT` -> print `Quit (core dumped)` and return `131`
  - any other signal -> return `128 + WTERMSIG(status)`
- otherwise return `1`

## Folder-Level Call Chain

For a parsed command segment, the execution path inside this folder is:

1. `exec_tree`
2. one of:
   - `exec_simple_command`
   - `exec_pipe`
   - `exec_redirection`
   - `exec_logical`
   - `exec_subshell`
3. recursive calls back into `exec_tree` for child AST branches
4. `handle_wait_status` whenever a child process must be normalized into a shell exit code