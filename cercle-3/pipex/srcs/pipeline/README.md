# Pipeline Module

This directory contains the code that turns a list of commands into a running
Unix pipeline. In the current `pipex` project, this package is the central
orchestration layer: it allocates the pipe array, forks one child per command,
assigns the correct stdin and stdout endpoints for each stage, and computes the
exit status returned by the whole program.

The code here does not parse commands and does not open files directly. Instead,
it coordinates the other packages:

- `command/` executes the final command string in each child
- `io/` handles infile, outfile, and here-doc descriptor setup
- `error/` provides a few shared failure helpers

## Pipe Allocation Path

`create_pipes` in `pipes.c` builds the pipe array used between command stages.

The steps are:

1. Allocate `nb - 1` pipe slots with `malloc(sizeof(t_pipe) * (nb - 1))`.
2. Return `NULL` immediately if allocation fails.
3. Loop from the first pipe to the last required pipe.
4. Call `pipe(pipes[i])` for each slot.
5. If any `pipe()` call fails, report the error through `exit_statement`, release the array, and return `NULL`.
6. Return the allocated array on success.

The `nb - 1` rule is the key design detail: a pipeline with `n` commands needs
exactly one fewer pipes than commands, because each pipe connects two adjacent
stages.

## Pipe Cleanup Path

`close_all_pipes` in `pipes.c` closes every read end and write end in the pipe array.

The steps are:

1. Loop over every pipe slot.
2. Close the write end.
3. Close the read end.
4. Continue until every pipe has been released.

This helper is used in both the parent and the child side once the relevant
descriptor duplication is already complete. Its job is not selective routing;
it is the final cleanup step after stdin and stdout have been wired.

## Pipeline Initialization Path

`init_pipes` in `pipex.c` decides whether any pipe array is needed at all.

The steps are:

1. Check `nb_cmds`.
2. If there is more than one command, call `create_pipes(nb_cmds)`.
3. If pipe creation fails, return `exit_statement("pipes", NULL, -1)`.
4. If there is only one command, leave the pipe pointer untouched and return success.

This matters because a one-command run still uses the same orchestration entry
point, but no inter-process pipe chain is required.

## Runtime Configuration Path

`pipex` in `pipex.c` builds the runtime state before any process is created.

The steps are:

1. Store the shifted argument vector in `cfg.argv`.
2. Compute the number of commands as `argc - 2`.
3. Store whether the output side should append or truncate.
4. Initialize the pipe pointer to `NULL`.
5. Call `init_pipes`.

The `argc - 2` rule reflects the project layout after normalization:

- `argv[0]` is the infile or temporary here-doc file
- `argv[1]` through `argv[nb_cmds]` are commands
- `argv[nb_cmds + 1]` is the outfile

So the pipeline layer always works with a compact layout where the file operands
bookend the command sequence.

## Fork Loop Path

`fork_processes` in `pipex.c` is the main child-creation loop.

The steps are:

1. Start from command index `0`.
2. Call `fork()` once per command.
3. If `fork()` fails, report the error through `exit_statement`.
4. If the returned pid is `0`, run the child path with `run_process(cfg, i, pipes)`.
5. If the current index is the last command, remember that pid as `last_pid`.
6. Continue until every command has been forked.
7. Return the pid of the last command.

The saved `last_pid` is important because the final program exit code should
follow the shell convention of reporting the status of the last pipeline stage,
not an arbitrary earlier child.

## Single-Command Setup Path

`setup_single_cmd` in `process.c` handles the special case where the pipeline
contains only one command.

The steps are:

1. Call `read_from_infile` to bind stdin.
2. Call `handle_output_file` to bind stdout.

In this mode there is no middle pipe routing at all. The one command reads from
the input side and writes directly to the output side.

## Last-Stage Output Selection Path

`handle_output_file` in `process.c` decides which outfile helper should be used.

The rule is:

- if `append_mode` is enabled, call `write_to_outfile_append`
- otherwise call `write_to_outfile`

This keeps append-versus-truncate behavior out of the main fork logic and makes
the output policy explicit in one small helper.

## Per-Child Descriptor Setup Path

`setup_process_io` in `process.c` is the main routing function for child stdin
and stdout.

It has four cases.

### Single command

If the current command is both the first and the last command, call
`setup_single_cmd`.

### First command in a multi-command pipeline

If `i == 0`, call `read_from_infile`.

That gives the child:

- stdin from the infile
- stdout to the write end of the first pipe

### Last command in a multi-command pipeline

If `i == cfg->nb_cmds - 1`, call `handle_output_file`.

That gives the child:

- stdin from the read end of the previous pipe
- stdout to the outfile

### Middle command

Otherwise wire both sides directly with `dup2`:

1. Duplicate `pipes[i - 1][READ_END]` onto standard input.
2. Duplicate `pipes[i][WRITE_END]` onto standard output.

This is the pure pipeline case where the command reads from the previous stage
and writes to the next stage without touching any file.

## Child Execution Path

`run_process` in `process.c` is the child-side entry point called immediately
after `fork()`.

The full flow is:

1. Call `setup_process_io(cfg, i, pipes)`.
2. If the pipeline has more than one command, close all inherited pipe ends.
3. Free the allocated pipe array in the child.
4. Call `execute_command(cfg->argv[i + 1])`.
5. If execution unexpectedly returns, exit with `EXIT_FAILURE`.

The close-and-free step is important. Once the child has duplicated the correct
pipe ends onto stdin and stdout, it no longer needs the full pipe array. Leaving
those descriptors open would keep extra pipe ends alive and could interfere with
end-of-file detection in other processes.

## Parent Post-Fork Cleanup Path

After all children are created, `pipex` handles the parent-side descriptor cleanup.

The steps are:

1. If there was more than one command, call `close_all_pipes` in the parent.
2. Wait for all children with `wait_children`.
3. Free the pipe array through `cleanup`.
4. Return the computed exit code.

The parent closes its copies of the pipe ends only after the whole fork loop is
done, so every child has had a chance to inherit the descriptors it needs.

## Wait and Exit-Code Path

`wait_children` in `pipex.c` collects the status of every child process and
decides which one becomes the program's return value.

The steps are:

1. Loop exactly `nb_cmds` times.
2. Call `wait(&status)` each time.
3. If `wait` fails, return `1`.
4. Compare the returned pid against `last_pid`.
5. If this is the last command and it exited normally, store `WEXITSTATUS(status)`.
6. If this is the last command and it was terminated by a signal other than `SIGPIPE`, store `128 + signal_number`.
7. Continue waiting until every child has been collected.
8. Return the final stored exit code.

This is the core shell-like status rule of the package: the program reports the
status of the last command in the pipeline, not the first failing child.

The explicit `SIGPIPE` check is also meaningful. A broken pipe in an upstream
stage should not override the final status when the shell-compatible behavior is
to follow the last command's result.

## Final Cleanup Path

`cleanup` in `pipex.c` only frees the pipe array pointer when it exists.

This helper is intentionally tiny, but it keeps the main `pipex` function easier
to scan by making the end-of-run cleanup explicit.

## Folder-Level Call Chains

The main orchestration chains in this subtree are:

1. `pipex` -> `init_pipes` -> `create_pipes`
2. `pipex` -> `fork_processes` -> `run_process`
3. `run_process` -> `setup_process_io` -> `read_from_infile` or `handle_output_file` or direct `dup2`
4. `handle_output_file` -> `write_to_outfile` or `write_to_outfile_append`
5. Parent path -> `close_all_pipes` -> `wait_children` -> `cleanup`

## Practical Design Tradeoff

The package keeps one orchestration model for both normal mode and here-doc
mode. The only difference is the `append_mode` flag and the normalized argument
vector passed in from the I/O layer.

That means the pipeline code does not need to know where the input came from.
It only needs to know:

- how many commands exist
- which file descriptors each stage should receive
- which child corresponds to the last command

This keeps the orchestration layer compact and makes the control flow easier to
reason about than a design with separate normal-mode and bonus-mode pipeline
engines.