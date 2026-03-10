# 🔧 **Source Pipeline** - *From arguments to forked processes*

> **A high-level map of the `srcs/` tree.**  
> This README explains how the source folders fit together to turn command-line
> arguments into a working shell pipeline with process orchestration, descriptor
> wiring, command parsing, and exit-status propagation.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Scope](https://img.shields.io/badge/Scope-srcs%2F-overview-1f6feb?style=for-the-badge)
![Architecture](https://img.shields.io/badge/Architecture-pipeline-success?style=for-the-badge)

---

## 📖 **Overview**

The `srcs/` directory is the operational heart of the project. It contains the
runtime code that turns validated arguments into a repeatable multi-process
pipeline:

1. validate command-line shape and detect `here_doc` mode
2. rewrite input side with temporary file in bonus mode
3. allocate pipe array when needed
4. fork one child process per command
5. wire stdin/stdout descriptors for each child
6. parse command strings and resolve executable paths
7. call `execve` in each child
8. wait for all children and return the last command's exit status

At a high level, the runtime behaves like this:

```text
core -> io -> pipeline -> fork -> fd setup -> command -> execve
                           |
                           v
                      wait/collect
```

`error/` supports the entire flow with shared failure helpers.

---

## 🚀 **Global Pipeline**

The full runtime pipeline across `srcs/` is:

1. `core/main.c` validates the argument count and calls `run_pipex`.
2. `core/pipex.c` decides whether the program is running in standard mode or `here_doc` bonus mode.
3. `io/here_doc.c` materializes a temporary here-doc file if bonus mode is active.
4. `pipeline/pipex.c` builds the `t_config` structure and allocates the pipe array when more than one command is present.
5. `pipeline/pipes.c` creates each inter-process pipe.
6. `pipeline/process.c` forks one child per command.
7. Each child uses `pipeline/process.c` and `io/io.c` to receive the correct stdin/stdout endpoints through `dup2`.
8. `command/parser.c` splits the raw command string into an argument vector.
9. `command/cmd.c` resolves the executable path directly or through `PATH`.
10. `command/cmd.c` calls `execve` with the resolved path and argument vector.
11. The parent process closes its own copies of the pipe descriptors as they are no longer needed.
12. `pipeline/process.c` waits for all children and computes the final exit status from the last command.

---

## 🗂️ **Top-Level Folders**

### `core/`

The control tower of the program.

- Validates the command-line argument count and rejects invalid shapes.
- Detects `here_doc` mode through the second argument.
- Decides whether to run standard mode or bonus mode.
- Normalizes the argv layout before the rest of the runtime begins.

In the global flow, `core/` is the entry and mode selection layer. It does not
parse commands, open files, or manage children—it only decides how the rest of
the runtime should start.

### `command/`

The command translation layer.

- Splits raw command strings into argument vectors.
- Resolves the executable directly (if it contains `/`) or through `PATH` search.
- Preserves shell-like `126` (not executable) and `127` (not found) failure semantics.
- Calls `execve` to replace the child process with the target command.

In the global flow, `command/` is the final handoff from shell-land to process
execution. It is intentionally simple and assumes space-separated arguments,
leaving advanced quoting or expansion out of scope.

### `io/`

The file-descriptor side of the project.

- Opens the infile and outfile.
- Switches between truncate mode (standard) and append mode (bonus).
- Connects descriptors to stdin and stdout with `dup2`.
- Implements the here-doc bonus path through a temporary file.
- Validates file accessibility before attempting to open.

In the global flow, `io/` is where the project touches the filesystem most
directly. It wires the correct endpoints so each child sees the right input and
output.

### `pipeline/`

The structural center of the runtime.

- Allocates the pipe array based on the number of commands.
- Forks one child process per command.
- Decides which child is first, middle, or last in the chain.
- Closes inherited descriptors at the right moment to avoid deadlocks.
- Waits for all children and computes the final exit status from the last command.

In the global flow, `pipeline/` is the process orchestration layer. It does not
decide what a command means—it decides how commands are connected together as
processes.

### `error/`

The small shared-support layer.

- Centralizes a few `perror`-based failure paths.
- Keeps return-code and cleanup behavior consistent across the codebase.
- Stays intentionally small so the real control flow remains visible in the calling code.

In the global flow, `error/` is supporting infrastructure rather than a pipeline
stage of its own.

---

## 🔄 **Typical Command Journey**

For a standard two-command pipeline like `< in cmd1 | cmd2 > out`, the trip
through `srcs/` looks like this:

1. `core/main.c` receives the arguments and validates the count (exactly 5 arguments expected).
2. `core/pipex.c` detects that `argv[1]` is not `"here_doc"`, so standard mode is active.
3. `pipeline/pipex.c` builds the configuration: `argv[0]` is the infile, `argv[1]` and `argv[2]` are the two commands, `argv[3]` is the outfile.
4. `pipeline/pipes.c` allocates one pipe (two file descriptors) since there are two commands.
5. `pipeline/process.c` forks the first child.
6. The first child uses `io/io.c` to connect stdin to the infile and stdout to the write end of the pipe.
7. `command/parser.c` splits `"cmd1"` into an argument vector.
8. `command/cmd.c` resolves the path for `cmd1` and calls `execve`.
9. The parent closes the write end of the pipe (no longer needed).
10. `pipeline/process.c` forks the second child.
11. The second child connects stdin to the read end of the pipe and stdout to the outfile.
12. `command/` resolves `cmd2` and calls `execve`.
13. The parent waits for both children, stores the exit status of `cmd2`, and returns it as the program's exit code.

---

## 🧩 **How the Folders Depend on Each Other**

- `core/` depends on `pipeline/` to run the actual multi-process logic.
- `pipeline/` depends on `io/` to wire descriptors and on `command/` to execute strings.
- `command/` depends on the environment `PATH` and filesystem access checks from `io/access.c`.
- `io/` depends on filesystem APIs and bonus-mode logic for here-doc handling.
- `error/` is a shared dependency used by all other folders.

The tree is structured so that each folder owns one clear responsibility, and
the dependencies flow downward through the runtime layers.

---

## 📊 **Data Layout Used Across `srcs/`**

The runtime packages all rely on one shared interpretation of the normalized
argument layout stored in `t_config`:

- `argv[0]` is the infile (or temporary here-doc file in bonus mode)
- `argv[1]` through `argv[nb_cmds]` are command strings
- `argv[nb_cmds + 1]` is the outfile

That layout is what allows the packages to stay coordinated without passing a
large number of separate values around.

The other important shared data type is `t_pipe`, which stores one pair of file
descriptors per pipe segment.

---

## 👨‍👩‍👧 **Parent and Child Responsibilities**

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

---

## ⚡ **Status Propagation Rule**

The whole runtime follows one important shell-like rule: **the program returns
the status of the last command in the pipeline.**

That means `srcs/` is not just about launching processes successfully. It is
also about preserving the behavior users expect from pipeline semantics.

This is why the code remembers the pid of the last child and treats that child's
status specially during the wait phase.

---

## 📚 **Reading Order**

If you want to understand the code from top to bottom, the most useful order is:

1. `core/` — entry point and mode selection
2. `io/` — understanding bonus-mode input rewriting and descriptor wiring
3. `pipeline/` — the actual multi-process control flow
4. `command/` — the final execution handoff
5. `error/` — the small shared helpers used along the way

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