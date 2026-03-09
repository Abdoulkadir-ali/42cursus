# Exec Module

Handles command execution, process management, builtins, environment manipulation, and heredoc support. This subsystem is responsible for running parsed commands, managing pipes and redirections, and integrating shell builtins.

---

## 📂 Directory Structure
- `srcs/exec/` — Execution layer root
  - `ast/` — AST-based execution: control flow, path resolution, pipes, redirections, and process waiting
  - `builtins/` — Builtin command drivers and glue to exec layer
  - `env/` — Environment helpers and builtin implementations
  - `heredoc/` — Heredoc generator, reader, and expansion

---

## 🏗️ How It Works

### Global Pipeline
1. The parser produces an AST that can still contain `TOKEN_HEREDOC` and `TOKEN_HERESTR` nodes.
2. The execution layer first materializes those input-producing nodes through the heredoc helpers.
3. Once temporary files are ready, heredoc and here-string nodes are rewritten as regular `TOKEN_RED_IN` nodes.
4. Execution then enters the AST dispatcher in `tree.c`.
5. Each AST node is routed to the exact executor for simple commands, pipes, redirections, logical operators, subshells, or sequencing.
6. Simple commands either stay in-process as builtins or fork and `execve` an external program.
7. Builtins reuse the environment helpers for `export`, `unset`, `cd`, `_`, `PWD`, and `OLDPWD` updates.
8. Any child-based execution path is normalized back into shell exit codes through the wait helpers.

### `ast/`
- **control.c**: Implements execution control flow (e.g., sequential, conditional, pipeline execution).
- **path.c**: Resolves executable paths using environment variables and search logic.
- **pipe.c**: Sets up and manages pipes for command pipelines.
- **redirection.c**: Handles input/output redirection, file descriptor manipulation.
- **simple.c**: Executes simple commands (no pipeline/redirection).
- **tree.c**: Traverses and executes AST nodes recursively.
- **wait.c**: Waits for child processes, collects exit statuses.

#### Pipeline Inside `ast/`
1. `exec_tree` is the entry point and dispatcher for every AST node.
2. `exec_tree` routes `TOKEN_WORD` to `exec_simple_command`.
3. `exec_tree` routes `TOKEN_PIPE` to `exec_pipe`.
4. `exec_tree` routes `TOKEN_RED_IN`, `TOKEN_RED_OUT`, `TOKEN_APPEND`, and heredoc-backed `TOKEN_RED_IN` nodes to `exec_redirection`.
5. `exec_tree` routes `TOKEN_AND` and `TOKEN_OR` to `exec_logical` with the proper short-circuit mode.
6. `exec_tree` routes `TOKEN_SUBSHELL` to `exec_subshell`.
7. `TOKEN_SEMICOLON` runs the left branch first, then the right branch through recursive `exec_tree` calls.

For a simple command, the pipeline is exact:
1. `exec_simple_command` returns `0` when no command name exists.
2. It calls `is_builtin(node->args[0], node->args)`.
3. If the command is a builtin, it returns `exec_builtin(node->args, state)` without forking.
4. Otherwise it resolves the executable path through `find_path`.
5. If path resolution fails, it returns `127` after printing the matching shell error.
6. If path resolution succeeds, it calls `run_external_command`.
7. `run_external_command` forks once, calls `child_execution` in the child, waits in the parent, and returns `handle_wait_status(status)`.

For a pipeline node, the pipeline is:
1. `exec_pipe` creates one pipe.
2. `fork_left_command` forks the left branch and connects stdout to the pipe write end.
3. `fork_right_command` forks the right branch and connects stdin to the pipe read end.
4. The parent closes both pipe descriptors.
5. `wait_for_children` waits for both processes and returns the normalized status of the right side.

For a redirection node, the pipeline is:
1. `exec_redirection` resolves the target descriptor with `get_target_fd`.
2. It opens the file through `open_redirection_file`.
3. It saves and replaces the descriptor through `setup_redirection`.
4. It executes the wrapped command through `exec_tree(node->left, state)`.
5. It restores the original descriptor before returning the wrapped command status.

Every child-based branch eventually passes through `handle_wait_status`, which converts `waitpid` results into shell exit codes such as `130` for `SIGINT` and `131` for `SIGQUIT`.

---

### `builtins/`
- **exec.c**: Dispatches builtin commands, integrates with exec layer.
- **init.c**: Initializes builtin command context and registration.
- **functions/**: Implements individual builtin command logic (e.g., `cd`, `echo`, `pwd`, `env`, `export`, `unset`, `exit`).

#### Pipeline Inside `builtins/`
1. `is_builtin` decides whether a command stays inside the shell process.
2. `exec_builtin` dispatches the command through the registry returned by `get_builtins`.
3. `init_builtins` wires the builtin names to `ft_echo`, `ft_cd`, `ft_pwd`, `ft_export`, `ft_unset`, `ft_env`, `ft_exit`, and `builtin_colon`.
4. `ft_echo`, `ft_env`, `ft_pwd`, and `builtin_colon` complete entirely inside their own file-level helpers.
5. `ft_export` and `ft_unset` delegate variable validation and updates to the env helpers in `srcs/exec/env`.
6. `ft_cd` delegates path resolution, CDPATH lookup, logical normalization, and `PWD` / `OLDPWD` updates to the helpers in `functions/cd` and `srcs/exec/env`.
7. `ft_exit` resolves the final status and terminates the shell process directly.

---

### `env/`
- **print.c**: Prints environment variables.
- **set.c**: Sets and updates environment variables.
- **utils.c**: Helper functions for environment manipulation.
- **process/**: Manages environment context for child processes.

#### Pipeline Inside `env/`
1. `ft_set_env` is the direct update entry used when execution helpers need to insert or replace one variable.
2. `ft_set_env` builds a new `KEY=VALUE` entry, finds an existing slot with `get_env_index`, then either replaces the old entry or appends a new one.
3. `print_sorted_env` builds a temporary list, sorts it, and prints entries in the `declare -x` format used by `export`.
4. `is_valid_ident`, `parse_export_arg`, and `report_invalid_identifier` perform export and unset validation.
5. `process_export_arg` is the main export-update path.
6. `process_export_arg` resolves whether the target variable already exists.
7. Existing keys flow through `process_existing_export` and `update_existing_env`.
8. New keys flow through `process_new_export` and `push_new_env_entry`.
9. Append syntax such as `VAR+=x` is normalized through `create_appended_entry` or `handle_append`, depending on whether the key already exists.

---

### `heredoc/`
- **consume.c**: Reads heredoc input from user, stores in temporary files.
- **expand.c**: Expands variables within heredoc input.
- **input.c**: Handles heredoc input stream setup.
- **quotes.c**: Manages quote handling in heredoc input.
- **read.c**: Reads heredoc content for command execution.
- **scan.c**: Scans heredoc delimiters and manages input flow.
- **utils.c**: Helper functions for heredoc management.

#### Pipeline Inside `heredoc/`
1. `scan_heredocs` walks the AST before normal execution starts.
2. For `TOKEN_HEREDOC`, it calls `handle_heredoc_input`.
3. `handle_heredoc_input` resolves the delimiter, allocates a temporary file, runs `read_heredoc_loop`, then rewrites the AST node as `TOKEN_RED_IN`.
4. For `TOKEN_HERESTR`, `scan_heredocs` calls `handle_herestr`, which writes the here-string payload into a temporary file and also rewrites the node as `TOKEN_RED_IN`.
5. `read_heredoc_loop` prepares the effective stop string with `prepare_stop_str`, switches to heredoc signal handling, then calls `read_heredoc_lines`.
6. `read_heredoc_lines` repeatedly calls `heredoc_read_line` and routes each line through `process_heredoc_line`.
7. Quoted heredocs stay literal through `process_line_quoted`.
8. Unquoted heredocs expand variables through `process_line_unquoted` and `expand_heredoc`.
9. EOF and `SIGINT` are handled explicitly so interrupted heredocs fail before the execution phase tries to use them.

---

## 🛠️ Developer Notes
- The top-level execution order is: heredoc materialization -> AST dispatch -> builtin or external execution -> wait-status normalization.
- Pipeline status follows the rightmost command because `wait_for_children` returns the normalized status of the second child.
- Redirections wrap recursive `exec_tree` calls by replacing descriptors before execution and restoring them afterward.
- Builtins that mutate shell state do so in-process, which is why env and `cd` helpers are part of this module instead of a separate child-only path.
- Heredoc nodes are converted into ordinary input-redirection nodes before command execution, so the AST executor can treat them like standard files.

For detailed function documentation, see the source files and header definitions in `includes/exec.h` and submodule headers.
