# Command Module

This directory contains the code that turns one raw command string into something `execve` can run. In the current `pipex` flow, this package is the bridge between the textual command stored in `argv` and the fully resolved executable path used inside each child process.

The implementation here is small, but it does several distinct jobs:

- split the command string into an argument vector
- resolve the executable either directly or through `PATH`
- release temporary parsing allocations
- preserve shell-like exit behavior when execution fails

## Parsing Path

`parse_command` in `parser.c` is the entry point for command splitting.

The steps are:

1. Reject a null command string and return `NULL` immediately.
2. Call `ft_split(cmd, ' ')`.
3. Return the resulting `char **` argument array to the caller.

This means the package assumes a simple whitespace-separated command format.
It does not implement shell quoting, escaping, or variable expansion. So a
string like `grep "hello world" file` is not interpreted with real shell rules;
it is only split on spaces.

That behavior matches the current scope of the project: `pipex` receives command
strings and prepares them just enough for direct execution, without trying to
reproduce a full shell parser.

## Cleanup Path

`free_args` in `parser.c` releases an argument array created by `parse_command`
or any equivalent NULL-terminated string array.

The steps are:

1. Return immediately if the array pointer is null.
2. Walk forward until the terminating null slot.
3. Free each individual string.
4. Free the outer array itself.

This helper is used throughout the command-resolution path whenever a split
array is no longer needed, especially for temporary `PATH` directory lists and
for parsed command arguments after a failed `execve`.

## Direct Resolution Path

`find_command_path` in `cmd.c` is the main resolver used before `execve`.

Its first rule is simple:

- if the command pointer is null, return it unchanged
- if `access(cmd, X_OK) == 0`, treat it as already executable and return it unchanged

This covers both absolute paths and relative executable paths such as:

- `/bin/ls`
- `./my_program`
- `../tool`

In this branch, the function does not allocate new memory. The returned pointer
is still the original token from the parsed argument vector.

## PATH Lookup Path

If the command is not directly executable, `find_command_path` falls back to
environment-based lookup.

The steps are:

1. Read `PATH` with `getenv("PATH")`.
2. If `PATH` is missing, return the original command unchanged.
3. Split the `PATH` string on `:` with `ft_split`.
4. Pass the resulting directory array to `search_in_paths`.

At this stage the resolver still has not decided whether the command is valid.
It is only preparing candidate directories to test.

## Candidate Construction Path

`search_in_paths` iterates through the split `PATH` entries.

For each directory, it calls `try_path`.

`try_path` performs the candidate build in two steps:

1. Join the directory and `/` into a temporary string.
2. Join that temporary string with the command name to produce the full candidate path.

Then it checks the candidate with `access(full_path, X_OK)`.

The result rules are:

- if the candidate is executable, return the newly allocated full path
- if not, free the candidate and continue searching

`search_in_paths` stops on the first valid executable, frees the split `PATH`
array with `free_args`, and returns the winning path.

If nothing matches, it still frees the directory list and returns `NULL`.

## Resolver Fallback Behavior

Back in `find_command_path`, the result of `search_in_paths` is interpreted like this:

- if a valid path was found, return that allocated string
- otherwise return the original command token

This fallback matters because the final failure decision is intentionally left to
`execve`. The command layer does not fully simulate shell diagnostics itself; it
prepares the best path it can and then lets execution determine the exact error.

## Execution Path

`execute_command` in `cmd.c` is the public entry point used by the pipeline
package inside each forked child.

The full flow is:

1. Parse the raw command string with `parse_command`.
2. If parsing fails or produces no program name, free what exists and exit with `127`.
3. Resolve the executable with `find_command_path(args[0])`.
4. Call `execve(cmd_path, args, environ)`.
5. If `execve` succeeds, control never returns.
6. If `execve` fails, store `errno`, clean up allocations, print the error, and exit with the right status code.

The use of `extern char **environ` means the command is executed with the
current process environment rather than with a separate reconstructed envp.

## Failure Exit Codes

When `execve` fails, `execute_command` preserves two important shell-like cases:

- `ENOENT` produces exit code `127`
- every other execution failure produces exit code `126`

That distinction is important because it separates:

- command not found
- command found but not executable, or another execution-time failure occurred

Before exiting, the function also checks whether `cmd_path` is a newly allocated
resolved path or just `args[0]` reused directly. It only frees `cmd_path` when
those two pointers differ.

## Memory Ownership Summary

The ownership rules in this directory are:

- `parse_command` returns a heap-allocated argument vector owned by the caller
- `find_command_path` sometimes returns the original token and sometimes a new allocated path
- `search_in_paths` always frees the temporary split `PATH` array before returning
- `execute_command` frees parsed arguments and any allocated resolved path only on failure, because a successful `execve` replaces the process image

This is why the pointer comparison `cmd_path != args[0]` matters: it tells the
code whether the resolver returned borrowed memory or owned memory.

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `execute_command` -> `parse_command` -> `find_command_path` -> `execve`
2. `find_command_path` -> `getenv` -> `ft_split` -> `search_in_paths`
3. `search_in_paths` -> `try_path`
4. Failure cleanup paths -> `free_args`

## Practical Limitation

The main limitation of this package is the parser itself: because it relies on
`ft_split(cmd, ' ')`, it cannot preserve quoted groups or escaped spaces.

So this module is best understood as a command-preparation layer for the 42
`pipex` project, not as a general-purpose shell parser.

That tradeoff keeps the runtime simple and aligned with the current project
scope: process creation, piping, redirection, and exit-status behavior are the
main goals, while full shell grammar is intentionally out of scope.