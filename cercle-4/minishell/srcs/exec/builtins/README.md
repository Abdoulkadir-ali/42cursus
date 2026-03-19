# Builtin Execution Pipeline

This directory contains the functions that detect, dispatch, and execute shell
builtins. The flow below is function-oriented and follows the exact calls used
by the executor.

## Dispatch Entry

`is_builtin` in `exec.c` decides whether a simple command should stay inside
the shell process.

Its rules are exact:

- reject a null command
- accept `.` immediately
- reject `env` when extra arguments are present, so that case falls back to an
  external command
- otherwise scan the builtin registry returned by `get_builtins`

`exec_builtin` in `exec.c` performs the actual dispatch.

The steps are:

1. Fetch the builtin table with `get_builtins()`.
2. Scan each entry until `args[0]` matches `builtins[i].name`.
3. Call `builtins[i].func(args, state)` and return its status.


Its behavior is:

- if `args[1]` is missing, print the filename and usage errors and return `2`
- otherwise return `0`

## Builtin Registry

`init.c` owns the builtin registry setup.

`init_builtin_entry` fills one table slot with a name and function pointer.

`init_builtins` wires the static registry in this exact order:

1. `echo` -> `ft_echo`
2. `cd` -> `ft_cd`
3. `pwd` -> `ft_pwd`
4. `export` -> `ft_export`
5. `unset` -> `ft_unset`
6. `env` -> `ft_env`
7. `exit` -> `ft_exit`
8. `:` -> `builtin_colon`

`get_builtins` lazily initializes the static array once, then returns the same
registry pointer for every later dispatch.

`builtin_colon` is the `:` builtin implementation.
It ignores its arguments and always returns `0`.

## Echo Path

`ft_echo` in `functions/echo.c` executes the echo builtin.

The steps are:

1. Call `parse_echo_options(args, &newline)`.
2. `parse_echo_options` consumes repeated `-n`, `-nn`, `-nnn`, and similar
	flags, and returns the first non-option index.
3. Call `print_echo_args(args, start)`.
4. `print_echo_args` writes arguments separated by one space.
5. If `newline` is still enabled, print the trailing newline.
6. Return `0`.

## Env Path

`ft_env` in `functions/env.c` prints the current environment.

The steps are:

1. Iterate over `state->envp`.
2. Print only entries that contain `=`.
3. Return `0`.

## Exit Path

`ft_exit` in `functions/exit.c` terminates the shell.

The steps are:

1. If `state->interactive_shell` is true, print `exit` to stderr.
2. Call `get_exit_status(args, &status, state)`.
3. `get_exit_status` uses `state->exit_code` when no explicit argument is
	provided.
4. Otherwise it calls `parse_exit_argument(args[1])`.
5. `parse_exit_argument` validates numeric conversion with `ft_safe_atoll` and
	exits with status `2` when the argument is not numeric.
6. If too many arguments are present, `get_exit_status` prints the related
	error, stores `1`, and returns.
7. `ft_exit` terminates the shell with `exit((unsigned char)status)`.

## Export Path

`ft_export` in `functions/export.c` handles environment creation and updates.

The steps are:

1. If there is no operand, call `handle_export_no_args(state)`.
2. `handle_export_no_args` prints the sorted environment and returns `0`.
3. Otherwise call `process_export_args(args, state)`.
4. `process_export_args` walks every operand starting at `args[1]`.
5. If an operand starts with `-`, return `handle_invalid_option(arg)`.
6. `handle_invalid_option` prints the option error and returns `2`.
7. Otherwise call `process_export_arg(args[arg_idx], state)`.
8. If any operand fails validation, keep the final builtin status at `1`.

## Pwd Path

`ft_pwd` in `functions/pwd.c` reports the current directory.

The steps are:

1. Try `getcwd(cwd, sizeof(cwd))`.
2. If it succeeds, print that path and return `0`.
3. Otherwise read `PWD` from `state->envp`.
4. If `PWD` exists, print it and return `0`.
5. If neither source works, call `perror("pwd")` and return `1`.

## Unset Path

`ft_unset` in `functions/unset.c` removes environment variables.

The steps are:

1. Iterate over operands from `args[1]` onward.
2. If one operand starts with `-`, return `ft_unset_handle_option(opt)`.
3. `ft_unset_handle_option` prints the usage error and returns `2`.
4. Skip operands that are not valid identifiers or that contain `=`.
5. Resolve each remaining identifier with `get_env_index`.
6. If the variable exists, call `ft_unset_remove_at(&state->envp, idx, state)`.
7. `ft_unset_remove_at` rebuilds the environment array without the removed
	entry and keeps `state->envp` synchronized.
8. Return `0` when the loop finishes.

## Cd Entry Path

`ft_cd` in `functions/cd/cd.c` is the entry point for the cd builtin.

The steps are:

1. Call `validate_cd_args(args)`.
2. If more than one operand is supplied, print `cd: too many arguments` and
	return `1`.
3. Call `get_cd_path(args, state)`.
4. If no path is resolved, return `1`.
5. Call `perform_cd(path, state)`.
6. Free the allocated path and return the result.

`resolve_home` resolves the path used by `cd` with no operand.

Its rules are:

- prefer `HOME` from the shell environment
- if `HOME` exists but is empty, fall back to `get_cwd_dup()`
- otherwise fall back to `getpwuid(getuid())`
- if no home directory is available, print `cd: HOME not set` and return `NULL`

`get_cwd_dup` duplicates the current working directory and falls back to an
empty string when `getcwd` fails.

## Cd Target Resolution

`get_cd_path` in `functions/cd/get.c` resolves the final target used by `cd`.

The steps are:

1. Call `get_path_from_args(args, state)`.
2. `get_path_from_args` chooses between:
	- `resolve_home(state)` for no operand or `--`
	- `handle_oldpwd(state)` for `-`
	- `ft_strdup(args[1])` otherwise
3. `handle_oldpwd` reads `OLDPWD`, prints it, and duplicates it.
4. Pass the selected path to `check_cdpath(path, state)`.
5. `check_cdpath` only runs CDPATH lookup when the target is relative and does
	not already contain `/`.
6. If `cdpath_find(path, cdpath)` returns a candidate, print it when
	appropriate and use that candidate.
7. Otherwise keep the original path.

## Cd CDPATH Search

`cdpath_find` in `functions/cd/utils.c` scans `CDPATH` one entry at a time.

For each entry it:

1. Extracts one token with `get_next_entry(cdpath, &start)`.
2. Builds a candidate with `build_candidate(entry, name)`.
3. `build_candidate` joins the entry and target name, and converts the result
	to an absolute path when the CDPATH entry itself is relative.
4. Passes the candidate to `check_candidate(candidate)`.
5. `check_candidate` accepts only existing directories with execute
	permission.
6. Returns the first accepted candidate, or `NULL` when no entry matches.

## Cd Logical Normalization

`perform_cd` in `functions/cd/perform.c` applies the directory change and
updates shell state.

The steps are:

1. Capture the previous directory with `get_oldpwd(state)`.
2. Call `change_directory(path, state)`.
3. `change_directory` first calls `normalize_logical(path, state)`.
4. If normalization succeeds, run `chdir(norm_path)`.
5. Otherwise run `chdir(path)`.
6. If `chdir` fails, return `handle_cd_error(path, oldpwd, NULL)`.
7. Compute the new logical directory with `get_newpwd(path, state)`.
8. Update `OLDPWD` and `PWD` through `ft_set_env`.
9. Free temporary strings and return `0`.

`normalize_logical` in `functions/cd/normalize.c` rebuilds the logical path.

The steps are:

1. Build the starting string with `build_base_path(path, state,
	&leading_slashes)`.
2. `build_base_path` selects one of:
	- `handle_absolute_path`
	- `handle_relative_with_pwd`
	- `handle_relative_with_cwd`
	- `ft_strdup(path)` as the final fallback
3. Tokenize the base path with `collect_components(base, &count)`.
4. `collect_components` fills a stack through `process_components`.
5. `process_components` repeatedly calls `extract_next_component` and then
	`add_component`.
6. `add_component` removes `.` entries, collapses `..`, and duplicates normal
	path components.
7. Pass the resulting stack to `norm_components(stack, count,
	leading_slashes)`.
8. `norm_components` returns a root string through `handle_root_path` when no
	components remain, otherwise calls `build_path_from_stack`.
9. `build_path_from_stack` computes the final length with `calc_len`, writes
	the string with `fill_path`, then frees the temporary stack.

`join_paths` is the shared helper used whenever two path fragments must be
concatenated without introducing duplicated separators.

## Folder-Level Call Chain

When builtin execution starts from the executor, the call flow in this
directory is:

1. `is_builtin`
2. `exec_builtin`
3. one of:
	- `ft_echo`
	- `ft_cd`
	- `ft_pwd`
	- `ft_export`
	- `ft_unset`
	- `ft_env`
	- `ft_exit`
	- `builtin_colon`

For `cd`, the internal call chain is:

1. `ft_cd`
2. `get_cd_path`
3. `perform_cd`
4. `normalize_logical` when logical path rebuilding is needed