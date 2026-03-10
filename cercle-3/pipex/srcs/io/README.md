# I/O Module

This directory contains the functions that prepare file descriptors for the
pipeline runtime. In `pipex`, this package is responsible for two separate but
closely related jobs:

- connecting child processes to the infile, outfile, and adjacent pipe ends
- implementing the `here_doc` bonus mode by materializing temporary input

Unlike the command package, this directory works directly with Unix file
descriptors, open modes, and `dup2`-based redirection.

## Access Validation Path

`check_file_access` in `access.c` is the small preflight helper for the input
file.

The steps are:

1. Ignore the `outfile` argument because this helper currently only validates the input side.
2. Call `access(infile, R_OK)`.
3. If the file is not readable, print the system error with `perror(infile)` and return `-1`.
4. Otherwise return `0`.

This path is intentionally narrow. It does not try to validate every later file
operation in advance. Actual open failures are still handled where they happen.

## Infile Wiring Path

`read_from_infile` in `io.c` prepares the first command in the pipeline.

The steps are:

1. Open the infile with `open(infile, O_RDONLY)`.
2. If the open fails, print the error and close `STDIN_FILENO`.
3. If the open succeeds, duplicate the file descriptor onto standard input with `dup2(fd, STDIN_FILENO)`.
4. Close the original file descriptor after duplication.
5. If there is more than one command, duplicate the write end of the first pipe onto standard output.

The important detail here is that this function prepares both sides of the first
process when needed:

- stdin comes from the infile
- stdout goes to the next pipe stage if the pipeline has more than one command

If opening the infile fails, the child does not exit here. Instead, stdin is
closed and the later execution path continues. That preserves shell-like
behavior where downstream commands may still run, but the failed input side is
effectively empty or broken.

## Outfile Truncate Path

`write_to_outfile` prepares the last command in normal mode.

The steps are:

1. Open the outfile with `O_WRONLY | O_CREAT | O_TRUNC` and mode `0644`.
2. If the open fails, print the error and close `STDOUT_FILENO`.
3. If it succeeds, duplicate the file descriptor onto standard output.
4. Close the original file descriptor after duplication.
5. If the pipeline contains more than one command, duplicate the read end of the previous pipe onto standard input.

This path is used for the ordinary `pipex infile cmd1 cmd2 outfile` behavior,
where the last command overwrites the destination file.

## Outfile Append Path

`write_to_outfile_append` is the bonus counterpart used by `here_doc` mode.

Its flow is almost identical to `write_to_outfile`, with one important change:

- the file is opened with `O_APPEND` instead of `O_TRUNC`

That means the last command writes at the end of the file rather than replacing
its previous contents.

This mirrors the shell behavior of:

```text
cmd1 << LIMITER | cmd2 >> outfile
```

## Here-Doc Temporary Name Path

`create_temp_filename` in `here_doc.c` builds the temporary filename used to
store here-doc content.

The steps are:

1. Read the current process id with `getpid()`.
2. Convert that id to a string with `ft_itoa`.
3. Join the fixed prefix `/tmp/.heredoc_tmp_` with the pid string.
4. Free the temporary pid string.
5. Return the allocated pathname.

The use of the process id reduces collisions between concurrent runs of the
program without requiring a hardcoded global filename.

## Here-Doc Read Loop

`read_heredoc_lines` is the interactive loop that captures the user input.

The steps are:

1. Print the prompt `heredoc> ` to standard output.
2. Read one line from standard input with `get_next_line`.
3. Stop immediately if end-of-file is reached.
4. Compare the line against the limiter.
5. If the limiter is matched exactly, free the line and stop.
6. Otherwise write the full line into the temporary file and continue.

The comparison logic uses two checks together:

- the prefix must match `limiter`
- the next character must be `\n` or `\0`

That prevents partial matches such as treating `EOFx` as if it were `EOF`.

## Here-Doc File Creation Path

`create_here_doc` is the public helper that materializes the temporary input file.

The steps are:

1. Build a unique temporary filename with `create_temp_filename`.
2. Open that path with `O_WRONLY | O_CREAT | O_EXCL` and mode `0600`.
3. If file creation fails, print `perror("heredoc temp file")` and return `NULL`.
4. Call `read_heredoc_lines` to fill the file.
5. Close the temporary file descriptor.
6. Return the allocated path.

The use of `O_EXCL` is important because it prevents silently reopening an
existing file at the same path.

## Here-Doc Dispatch Path

`handle_heredoc_mode` is the top-level entry used by `main` when the first
argument is `here_doc`.

The flow is:

1. Reject invalid argument counts smaller than six and print the bonus usage string.
2. Create the temporary here-doc file with `create_here_doc(argv[2])`.
3. If creation fails, return `1` immediately.
4. Replace `argv[2]` with the temporary file path.
5. Call `pipex(argv + 2, argc - 2, 1)` so the normal pipeline engine runs in append mode.
6. After `pipex` returns, unlink the temporary file.
7. Free the allocated file path.
8. Return the pipeline exit code.

This design is a useful simplification: instead of creating a separate runtime
path for here-doc execution, the I/O layer rewrites the arguments so the normal
pipeline engine can reuse its existing infile logic.

## Descriptor Strategy Summary

The package follows a consistent descriptor policy:

- open the needed file
- duplicate it onto stdin or stdout with `dup2`
- close the original descriptor immediately after duplication

That keeps the child process state simple and avoids carrying extra file
descriptors longer than necessary.

When an open fails, the code closes the corresponding standard descriptor rather
than exiting inside the helper. That leaves the higher-level process flow in
control of what happens next.

## Folder-Level Call Chains

The main call chains in this subtree are:

1. `check_file_access` -> `access`
2. `read_from_infile` -> `open` -> `dup2`
3. `write_to_outfile` -> `open` -> `dup2`
4. `write_to_outfile_append` -> `open` -> `dup2`
5. `create_here_doc` -> `create_temp_filename` -> `read_heredoc_lines`
6. `handle_heredoc_mode` -> `create_here_doc` -> `pipex` -> `unlink`

## Practical Design Tradeoff

The here-doc implementation writes its content to a temporary file rather than
feeding it through an anonymous pipe.

That choice has two consequences:

- the normal infile path can be reused with almost no extra branching
- cleanup becomes explicit because the temporary file must be unlinked after execution

For this project, that tradeoff keeps the control flow easy to understand and
fits the small size of the codebase well.