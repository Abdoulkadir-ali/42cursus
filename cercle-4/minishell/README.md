# 🐚 **Minishell** - *As beautiful as a shell*

> **A minimal bash-like shell implementation.**  
> Recreating the core functionality of a Unix shell in C.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Status](https://img.shields.io/badge/Status-In%20Progress-yellow?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)

---

## 📖 **Overview**

**Minishell** is a 42 school project that involves creating a simplified shell. The goal is to understand how a shell works under the hood: process creation, synchronization, file file descriptors, pipes, redirections, and signal handling.

---

## ✨ **Features**

### 🧠 **Parsing & Expansion**
- **Robust Tokenizer**: Handles complex command structures.
- **Quote Handling**: Supports single (`'`) and double (`"`) quotes.
  - Double quotes expand variables (`$USER`).
# minishell

A compact POSIX-like shell implemented for the 42 cursus. This repository contains
the tokenizer, parser, expansion/wildcard logic, heredoc handling, and the
execution layer including builtins.

## Highlights

- Tokenizer & AST-based execution
- Quote handling and environment variable expansion
- Builtins: `echo`, `cd`, `pwd`, `env`, `export`, `unset`, `exit`
- Heredoc support with safe temporary-file creation
- Ongoing refactors to reduce exported symbols and improve modularity

## Layout (important folders)

- `srcs/core` — main, signal handling, input loop
- `srcs/parsing` — tokenizer, expansion, wildcard matching, AST builder
- `srcs/exec` — execution layer, builtins, heredoc, env management
   - `srcs/exec/builtins` — builtin wrappers
   - `srcs/exec/env` — env helpers and builtin implementations
   - `srcs/exec/heredoc` — heredoc generator/reader
- `includes` — project headers
- `packages/libft` — bundled libft static library

## Build

Requirements: a POSIX toolchain (`cc`), `make`, and `readline`.

# Minishell — a small, thoughtful shell implementation

This project is an educational, focused implementation of a POSIX-like
command-line shell written in C. Building a shell is an excellent way to gain
hands-on experience with processes, file descriptors, inter-process
communication, parsing, and Unix signals — all while producing a useful and
tangible program.

The codebase is intentionally compact and readable so you can explore and
modify the key subsystems without getting lost in unrelated complexity.

Why this project is valuable:

- It demonstrates real-world systems programming patterns: fork/exec,
   redirection, and safe resource cleanup.
- It provides a practical exercise in tokenizer/parser design and
   transformation (expansion and AST-based execution).
- It is a teachable codebase: helper functions are kept small, and many
   utilities are file-local (`static`) to make reasoning about the API surface
   easier.

## What this shell supports

- Command execution and pipelines (`|`)
- Simple redirections: input `<`, output `>`, append `>>`
- Heredoc (`<<`) with secure temporary-file handling
- Variable expansion and quote handling
- Common builtins: `echo`, `cd`, `pwd`, `env`, `export`, `unset`, `exit`

## Project layout (quick guide)

Top-level folders you will interact with:

- `includes/` — project headers and public APIs.
- `srcs/core/` — program entry (`main.c`), signal setup and the interactive
   loop.
- `srcs/parsing/` — tokenizer, expansion, wildcard matching and AST builder.
- `srcs/exec/` — execution layer and builtins. Subfolders:
   - `builtins/` — builtin command drivers and glue to exec layer.
   - `env/` — environment helpers and `export`/`unset` implementations.
   - `heredoc/` — heredoc handling and temporary-file creation.
   - `exec/` — process launching, pipe setup and redirection handling.
- `packages/libft/` — bundled `libft` static library used at link time.

File and design conventions:

- Keep helper functions `static` if they are only used in a single file.
- Prefer explicit ownership of heap memory: document whether a caller must
   free returned strings.
- Group related local variables into small context structures where it
   simplifies function signatures.

## Build instructions

Prerequisites: a C toolchain (`cc`), `make`, and the `readline` development
headers.

Build from the repository root:

```bash
make
```

Common targets:

- `make` — build the binary `minishell`.
- `make clean` — remove object files.
- `make fclean` — remove object files and the executable.
- `make re` — full rebuild.

## Running the shell

Start an interactive shell:

```bash
./minishell
```

Run a single command and exit:

```bash
./minishell -c "echo hello"
```

## Examples and behaviors

- Variable expansion respects quoting: `$VAR` inside double quotes expands,
   single quotes are literal.
- `export` and `unset` affect the runtime environment used by subsequent
   commands in the same session.
- Heredoc input is written to a secure temporary file which is then used as
   stdin for the command; this avoids races and permissions issues.

## Testing and debugging

- There is a `42_minishell_tester/` directory with community test scripts.
   You can adapt or use its scripts to validate behavior.
- To check memory safety, run the shell under Valgrind while exercising
   builtins and pipelines:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./minishell
```

- Use the environment-driven debug hooks in the code (`MINI_DEBUG_*`) to
   enable verbose token or execution logging when needed.

## Developing and contributing

Contributions are welcome. Suggested workflow:

1. Create a feature branch for each logical change (e.g. `feature/wildcard`).
2. Keep commits small and focused; include a test case when behavior changes.
3. Run `make` and the test scripts locally before opening a PR.

Coding preferences in this repo:

- Small, well-named functions (a function-per-concept helps readability).
- Limit the number of non-static symbols exported by a file — helpers should
   be `static` when possible.
- Check return values and propagate errors; avoid silent failures.

## Further improvements you might try

- Add job control (`fg`, `bg`) and signal-aware terminal control.
- Improve the parser to support more shell grammar constructs.
- Add a test harness that runs a matrix of shell commands and validates
   outputs and exit codes.

## License and attribution

This repository includes a bundled test harness (`42_minishell_tester`) which
may have its own license; check `42_minishell_tester/LICENSE`. Use this code
for learning and experimentation — adapt licenses as appropriate for your
use.

---

If you want, I can add a `CONTRIBUTING.md` with a checklist and a short run
book for developers (valgrind, test commands, CI hints). Tell me and I will
add it.

Example:

```bash
bash 42_minishell_tester/tester.sh a
```

## Recent refactors / notes

- `export` logic and helpers were reorganized under `srcs/exec/env`.
- Introduced a single `t_global_state g_state` and compatibility macros in
   `includes/core.h` (e.g. `g_envp`, `g_exit_code`, `g_last_signal`).
- Many helper functions were made `static` to reduce the public symbol surface.

If you move files, update `Makefile`'s `SRCS` list.

## Contributing

Open small, focused PRs. Run `make` and the tester locally before submitting.
Prefer `static` helpers when functions are only used in a single file.

---

If you'd like, I can add a short development guide (valgrind usage, test
matrix, recommended coding style). Tell me what to include next.
