# 🧭 **Source Pipeline** - *How the shell moves from prompt to process*

> **A high-level map of the `srcs/` tree.**  
> This README explains how the source folders fit together in the global
> minishell pipeline, from startup and input reading to parsing, execution, and
> runtime state management.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Scope](https://img.shields.io/badge/Scope-srcs%2F-overview-1f6feb?style=for-the-badge)
![Architecture](https://img.shields.io/badge/Architecture-pipeline-success?style=for-the-badge)

---

## 📖 **Overview**

The `srcs/` directory is the operational heart of the project. It contains the
runtime code that turns a shell session into a repeatable pipeline:

1. initialize shell-owned state
2. read one logical command line
3. tokenize and validate the input
4. expand variables and wildcards
5. build an AST
6. prepare heredocs and redirections
7. execute builtins or external commands
8. store the resulting status back into shell state

At a high level, the shell behaves like this:

```text
core -> input -> parsing -> exec
          ^                    |
          |                    v
        state <----------------+
```

`state/` supports every stage, while `lib/` provides small shared utility code.

---

## 🚀 **Global Pipeline**

The full runtime pipeline across `srcs/` is:

1. `core/` starts the shell through `main` and `minishell`.
2. `state/` duplicates `envp`, initializes shell flags, normalizes `SHLVL`, and installs the right signal mode.
3. `input/reader` reads one physical or multiline command from `readline` or standard input.
4. `input/process` hands that logical line to the parsing pipeline.
5. `parsing/tokenizer` converts raw text into a token stream and rejects invalid syntax.
6. `parsing/env` expands `$VARIABLE` references and performs shell-style split logic.
7. `parsing/wildcard` expands active `*` and `?` patterns against directory entries.
8. `parsing/ast` builds the execution tree that represents commands, pipes, redirections, logical operators, and subshells.
9. `exec/heredoc` materializes heredocs and here-strings before normal execution begins.
10. `exec/ast` walks the AST and dispatches each node to the proper execution path.
11. `exec/builtins` keeps shell-owned commands in-process when required.
12. `exec/env` updates and queries the mutable runtime environment used by builtins and child execution.
13. Final command status is written back into the shell state so the next loop iteration sees the correct exit code.

---

## 🗂️ **Top-Level Folders**

### `core/`

The control tower of the shell.

- Starts the program and selects interactive mode or `-c` mode.
- Owns the main read-execute loop.
- Bridges startup, input acquisition, and final shutdown.
- Treats the other subsystems as staged services in the larger pipeline.

In the global flow, `core/` is the entry and coordination layer.

### `input/`

The command acquisition and preprocessing layer.

- Reads input from the terminal or stdin.
- Detects incomplete constructs such as unmatched quotes, parentheses, trailing operators, or trailing backslashes.
- Merges multiple physical lines into one logical command when continuation is required.
- Splits a validated token stream into semicolon-delimited execution segments.

In the global flow, `input/` is the handoff between user text and parseable shell data.

### `parsing/`

The transformation layer that turns raw shell text into structured execution data.

- `tokenizer/` builds tokens and validates shell syntax.
- `env/` expands variables and applies shell-style split behavior.
- `wildcard/` resolves filesystem matches for glob patterns.
- `ast/` constructs the command tree used by execution.

In the global flow, `parsing/` is the stage that converts text into meaning.

### `exec/`

The runtime execution layer.

- Prepares heredocs and here-strings.
- Walks the AST.
- Executes simple commands, pipelines, redirections, subshells, and logical operators.
- Decides whether a command runs as a builtin in the shell process or as an external program through `fork` and `execve`.

In the global flow, `exec/` is where parsed intent becomes actual process behavior.

### `state/`

The shared runtime state layer.

- Creates the shell-owned environment copy.
- Maintains `exit_code`, syntax flags, and expansion flags.
- Updates `SHLVL` during startup.
- Switches signal handling between interactive, blocking, and heredoc modes.

In the global flow, `state/` is the persistent context that every other folder reads from or writes to.

### `lib/`

The small shared-support layer.

- Hosts project-local helpers that do not belong to a larger subsystem.
- Currently contains common error-printing support used by multiple runtime paths.

In the global flow, `lib/` is supporting infrastructure rather than a pipeline stage of its own.

---

## 🔄 **Typical Command Journey**

For a normal interactive command, the trip through `srcs/` looks like this:

1. `core/minishell.c` starts an iteration of the shell loop.
2. `state/` provides the current environment and installs interactive signals.
3. `input/reader` returns one complete logical line.
4. `input/process` tokenizes that line and checks syntax.
5. `parsing/` expands variables and wildcards, then builds an AST.
6. `exec/heredoc` prepares temporary input files if heredocs exist.
7. `exec/ast` executes the tree.
8. `exec/builtins` or external-process helpers perform the actual command work.
9. The resulting exit status is stored in the active shell state.
10. `core/` starts the next prompt with that updated state.

---

## 🧩 **How the Folders Depend on Each Other**

- `core/` depends on `input/` and `state/` directly.
- `input/` depends on `parsing/` and triggers the first execution handoff.
- `parsing/` prepares the token and AST data that `exec/` consumes.
- `exec/` depends on `state/` for environment and signal-sensitive behavior.
- `exec/env` feeds environment updates back into the same shell-owned state created by `state/`.
- `lib/` provides low-level helpers used wherever shared behavior is needed.

This is why the tree feels linear at first glance, but actually behaves like a loop:

```text
startup -> read -> parse -> expand -> build -> execute -> update state -> prompt again
```

---

## 🛠️ **Reading Guide**

If you want to understand the project from top to bottom, read the folders in
this order:

1. `core/`
2. `state/`
3. `input/`
4. `parsing/tokenizer/`
5. `parsing/env/`
6. `parsing/wildcard/`
7. `parsing/ast/`
8. `exec/heredoc/`
9. `exec/ast/`
10. `exec/builtins/` and `exec/env/`

That order follows the same mental model as the actual runtime pipeline.

---

## 📚 **Submodule READMEs**

For the detailed function-oriented breakdowns, continue with:

- [srcs/core/README.md](srcs/core/README.md)
- [srcs/input/README.md](srcs/input/README.md)
- [srcs/parsing/README.md](srcs/parsing/README.md)
- [srcs/exec/README.md](srcs/exec/README.md)
- [srcs/state/README.md](srcs/state/README.md)

This file stays intentionally high-level so the rest of the `srcs/` READMEs can
go deeper into each stage.