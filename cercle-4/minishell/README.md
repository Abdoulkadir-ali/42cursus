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

```bash
make
```

Targets: `make`, `make clean`, `make fclean`, `make re`.

## Run

Interactive:

```bash
./minishell
```

Non-interactive (single command):

```bash
./minishell -c "echo hello"
```

## Testing

There is a `42_minishell_tester/` directory with the external tester used during
development. You can run its scripts or your own tests.

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
