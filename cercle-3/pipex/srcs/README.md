# Source Modules

This directory contains the full runtime implementation of `pipex`. Every stage
of the program after argument parsing lives here: startup dispatch, command
preparation, descriptor wiring, process orchestration, and shared error paths.

At a high level, `srcs/` is where the project stops being a list of command-line
arguments and starts behaving like a shell pipeline.

The tree is intentionally split by responsibility rather than by execution order.
That means each package stays small and focused, while the overall runtime still
forms one clear pipeline when the folders are viewed together.

## Top-Level Package Layout

The source tree is currently divided into five packages:

- `core/` for program entry and mode selection
- `command/` for turning raw command strings into executable argv/path data
- `io/` for file redirection and here-doc materialization
- `pipeline/` for pipe allocation, forking, child setup, and exit-status collection
- `error/` for small shared failure helpers

Those packages are not independent subsystems in the abstract. They form one
runtime chain where each package prepares the next one.

## Global Runtime Flow

The practical flow through `srcs/` is:

1. `core/` validates the command-line shape and decides whether the program is running in normal mode or `here_doc` mode.
2. `io/` may rewrite the effective input side in bonus mode by creating a temporary here-doc file.
3. `pipeline/` builds the execution configuration and allocates the inter-process pipe array when more than one command is present.
4. `pipeline/` forks one child per command.
5. Each child uses `pipeline/` plus `io/` to receive the correct stdin/stdout endpoints.
6. Each child hands its raw command string to `command/`.
7. `command/` parses the string, resolves the executable path, and calls `execve`.
8. The parent waits for all children and returns the exit status of the last command.

That same logic can be sketched more compactly like this:

```text
main -> mode selection -> pipe allocation -> fork -> fd setup -> command resolution -> execve
                                              |
                                              v
                                         wait/collect
```

The important thing about this shape is that `pipex` does not have one giant
monolithic function that does everything. Instead, the packages cooperate to
build the same end result in layers.

## How the Packages Fit Together

### `core/`

`core/` is the narrowest package in the tree, but it is the entry gate for the
entire program.

Its job is to:

- reject invalid argument counts
- detect `here_doc`
- normalize the argv layout before the rest of the runtime begins

It does not parse commands, open files, or manage children. It only decides how
the rest of the runtime should start.

### `command/`

`command/` owns the translation from a raw command string to an executable call.

Its job is to:

- split the command string into an argument vector
- resolve the executable directly or through `PATH`
- preserve shell-like `126` and `127` failure semantics

This package is intentionally simple. It is not a full shell parser. It assumes
space-separated arguments and leaves advanced quoting or expansion behavior out
of scope.

### `io/`

`io/` owns the file-descriptor side of the project.

Its job is to:

- open the infile and outfile
- switch between truncate and append mode
- connect descriptors to stdin and stdout with `dup2`
- implement the here-doc bonus path through a temporary file

This package is where the project touches the filesystem most directly.

### `pipeline/`

`pipeline/` is the structural center of the runtime.

Its job is to:

- allocate the pipe array
- fork one process per command
- decide which child is first, middle, or last
- close inherited descriptors at the right moment
- wait for children and compute the final status

This package does not decide what a command means. It decides how commands are
connected together as processes.

### `error/`

`error/` is the smallest package, but it exists to keep repetitive low-level
failure logic out of the main orchestration code.

Its job is to:

- centralize a few `perror`-based failure paths
- keep return-code and cleanup behavior consistent where these helpers are used

The package stays intentionally small so the real control flow remains visible
in the calling code.

## Data Layout Used Across `srcs/`

The runtime packages all rely on one shared interpretation of the normalized
argument layout stored in `t_config`:

- `argv[0]` is the infile or temporary here-doc file
- `argv[1]` through `argv[nb_cmds]` are command strings
- `argv[nb_cmds + 1]` is the outfile

That layout is what allows the packages to stay coordinated without passing a
large number of separate values around.

The other important shared data type is `t_pipe`, which stores one pair of file
descriptors per pipe segment.

## Parent and Child Responsibilities

One of the easiest ways to understand `srcs/` is to split the runtime into
parent-side and child-side responsibilities.

### Parent side

The parent process is responsible for:

- validating startup conditions
- creating the pipe array
- forking each child
- closing its own copies of the pipe descriptors
- waiting for every child
- returning the final program exit code

### Child side

Each child process is responsible for:

- receiving the correct stdin/stdout setup
- closing inherited descriptors it no longer needs
- executing exactly one command string

This parent/child split is the main reason the tree is arranged the way it is:
`pipeline/` coordinates process structure, `io/` wires descriptors, and
`command/` performs the final handoff into `execve`.

## Status Propagation Rule

The whole runtime follows one important shell-like rule: the program returns the
status of the last command in the pipeline.

That means `srcs/` is not just about launching processes successfully. It is
also about preserving the behavior users expect from pipeline semantics.

This is why the code remembers the pid of the last child and treats that child's
status specially during the wait phase.

## Build Relationship

The root `Makefile` compiles the entire `srcs/` tree recursively. That has two
practical consequences:

- folder organization matters because it defines how the project is documented and navigated
- adding a new source file inside `srcs/` does not require editing a hardcoded source list

The tree is therefore both a runtime structure and a maintainability structure.

## Reading Order

If you want to understand the code from top to bottom, the most useful order is:

1. `core/`
2. `io/` for understanding bonus-mode input rewriting
3. `pipeline/` for the actual multi-process control flow
4. `command/` for the final execution handoff
5. `error/` for the small shared helpers used along the way

That order follows the real runtime path closely enough that each next folder
answers the obvious question raised by the previous one.

## Related Files

- `../includes/pipex.h` — shared declarations used by every package
- `../Makefile` — recursive build rules for the source tree
- `core/README.md` — startup and dispatch details
- `command/README.md` — command parsing and resolution details
- `io/README.md` — descriptor and here-doc details
- `pipeline/README.md` — process orchestration details
- `error/README.md` — shared error helper details