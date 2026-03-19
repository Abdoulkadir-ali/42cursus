# 🐚 **Minishell** - *A small shell with a full pipeline behind it*

> **A 42 minishell implementation in C.**  
> This project recreates the essential behavior of a Unix shell: reading
> commands, parsing them, expanding them, building execution structures, and
> running them with the correct process, redirection, and signal behavior.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Project](https://img.shields.io/badge/Project-42%20Minishell-1f6feb?style=for-the-badge)
![Architecture](https://img.shields.io/badge/Architecture-Modular-success?style=for-the-badge)

---

## 📖 **Overview**

Minishell is an educational shell project focused on the parts of Unix command
execution that matter most:

- process creation and waiting
- pipes and file-descriptor redirections
- shell tokenization and syntax validation
- environment expansion and wildcard expansion
- AST-based execution
- signal-aware interactive behavior
- in-process builtins that mutate shell state

The codebase is organized as a real pipeline. A line of user input moves
through reading, tokenization, expansion, AST building, heredoc preparation,
and execution, then feeds its exit status back into the next prompt cycle.

---

## ✨ **What This Shell Supports**

- interactive prompt mode
- command-line mode with `-c`
- pipelines with `|`
- logical operators `&&` and `||`
- command grouping with parentheses / subshell execution
- redirections `<`, `>`, `>>`, heredoc `<<`, and here-string handling
- environment variable expansion
- quote-aware parsing and expansion
- wildcard expansion with `*` and `?`
- builtin commands: `echo`, `cd`, `pwd`, `env`, `export`, `unset`, `exit`

---

## 🏗️ **Global Pipeline**

At a high level, the shell runs this pipeline:

```text
startup -> read -> tokenize -> validate -> expand -> build AST -> prepare heredocs -> execute -> store status
```

In folder terms, the runtime flow is:

```text
core -> input -> parsing -> exec
          ^                    |
          |                    v
        state <----------------+
```

The stages are:

1. `core/` starts the shell and owns the main loop.
2. `state/` initializes shell-owned environment data, `SHLVL`, and signal modes.
3. `input/` reads one logical command line, including multiline continuation.
4. `parsing/tokenizer/` builds a token list and checks syntax.
5. `parsing/env/` expands variables and performs shell-style split behavior.
6. `parsing/wildcard/` expands active wildcard patterns.
7. `parsing/ast/` converts the transformed tokens into an execution tree.
8. `exec/heredoc/` materializes heredoc input before normal execution starts.
9. `exec/ast/` walks the tree and dispatches commands, pipes, redirections, logic, and subshells.
10. `exec/builtins/` and `exec/env/` handle shell-owned builtins and mutable environment updates.
11. The final status is written back into shell state for the next iteration.

---

## 🗂️ **Project Layout**

### `srcs/`

The full implementation tree.

- `srcs/core/` — program entry and the main shell loop
- `srcs/input/` — reading and preprocessing command lines
- `srcs/parsing/` — tokenization, expansion, wildcard logic, and AST building
- `srcs/exec/` — execution, builtins, heredocs, environment mutation
- `srcs/state/` — shell-owned runtime state and signal policy
- `srcs/lib/` — small shared runtime helpers

For the high-level source-tree guide, see [srcs/README.md](srcs/README.md).

### `includes/`

The public API layer of the project.

- `core.h` — top-level program entry points
- `input.h` — input pipeline APIs
- `parsing.h` — tokens, AST, expansion, wildcard, and parser APIs
- `exec.h` — execution and builtin APIs
- `state.h` — shell state and signal APIs
- `lib.h` — shared utility helpers

For the header-layer overview, see [includes/README.md](includes/README.md).

### `packages/libft/`

Bundled `libft` dependency used by the shell at build and runtime.

### Test and helper folders

- `minishell_tester/` — bash-based tester and manual test assets
- `minishell_tester2/` — python-based tester and generated case runner

---

## 🧠 **Why the Architecture Looks Like This**

This project deliberately separates responsibilities:

- `input/` deals with acquiring a complete command line
- `parsing/` turns text into structured shell data
- `exec/` turns that structured data into actual runtime behavior
- `state/` keeps the environment and signal-sensitive state consistent across the whole shell

That split keeps the project easier to reason about than a shell built as one
large file with shared global logic everywhere.

---

## ⚙️ **Build**

Prerequisites:

- `cc`
- `make`
- `readline` and its development headers

Build from the repository root:

```bash
make
```

Useful targets:

- `make` — build `minishell`
- `make clean` — remove object files
- `make fclean` — remove object files and the executable
- `make re` — full rebuild

---

## ▶️ **Run**

Start the interactive shell:

```bash
./minishell
```

Run one command with `-c`:

```bash
./minishell -c "echo hello"
```

---

## 🔬 **Testing**

This repository already includes tester folders you can use:

- `minishell_tester/`
- `minishell_tester2/`

Typical examples:

```bash
bash minishell_tester/tester
```

```bash
python3 minishell_tester2/main.py
```

For memory checking, Valgrind is still useful:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./minishell
```

---

## 📚 **Documentation Map**

The repository now includes subsystem READMEs that describe the shell in more
detail:

- [srcs/README.md](srcs/README.md) — high-level source pipeline
- [includes/README.md](includes/README.md) — public header and API map
- [srcs/core/README.md](srcs/core/README.md) — startup and main-loop flow
- [srcs/input/README.md](srcs/input/README.md) — reader and input-processing flow
- [srcs/parsing/README.md](srcs/parsing/README.md) — tokenization, expansion, AST, wildcard flow
- [srcs/exec/README.md](srcs/exec/README.md) — heredoc and execution flow
- [srcs/state/README.md](srcs/state/README.md) — runtime state and signal flow

Those files are the best place to read the implementation pipeline one stage at
a time.

---

## 🛠️ **Development Notes**

- Keep helper functions `static` when they are local to one translation unit.
- Treat ownership clearly for allocated strings and lists.
- Keep the pipeline readable: reader -> parser -> executor should stay easy to follow.
- If files move, update the `SRCS` list in the `Makefile`.

---

## 🚧 **Potential Next Steps**

- extend the grammar further
- add job control
- expand the automated test matrix
- keep reducing unnecessary exported symbols across modules
