# 🐚 **Minishell** - *A small shell with a full pipeline behind it*

> **A 42 minishell implementation in C.**  
> This project recreates the essential behavior of a Unix shell: reading commands, fracturing them into tokens, executing deep macro expansions, compiling an Abstract Syntax Tree (AST), and driving physical OS `fork()` and `dup2()` interactions to manifest pipelines, redirections, and subshells perfectly identical to normal Bash semantics.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Project](https://img.shields.io/badge/Project-42%20Minishell-1f6feb?style=for-the-badge)
![Architecture](https://img.shields.io/badge/Architecture-Modular-success?style=for-the-badge)

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

## 🗺️ **Global Pipeline & Data Flow**

At a high level, the shell runs this exact pipeline:
`startup -> read -> tokenize -> expand -> build AST -> spool heredocs -> execute -> store status`

Rather than a massive single loop, the architecture relies on strict translation boundaries visualized below:

```mermaid
stateDiagram-v2
    [*] --> core: Binary Execution
    
    state core {
        main_loop: REPL Polling
        core --> input: Requests text
    }
    
    state input {
        readline --> tokenizer: Yields char *line
    }
    
    state parsing {
        tokenizer: get_next_token()
        env_expand: macro & glob resolving
        ast_build: Compiles recursive tree
        
        tokenizer --> env_expand
        env_expand --> ast_build
    }
    
    input --> parsing
    parsing --> exec: Yields t_ast *root
    
    state exec {
        heredocs: pre-execution spooling
        dispatcher: exec_tree()
        builtins: in-memory mutation
        external: fork() + execve()
        
        heredocs --> dispatcher
        dispatcher --> builtins
        dispatcher --> external
    }
    
    exec --> state: exit() or return status
    state --> main_loop: Resets REPL context
```

---

## 🧱 **Subsystems Matrix**
| Subsystem Folder | Core Responsibility | Consumes | Produces |
| :--- | :--- | :--- | :--- |
| **`srcs/core/`** | Global Orchestration | Binary launch `char **envp` | Infinite REPL lifecycle. |
| **`srcs/input/`** | I/O Reading | Keyboard / File descriptor | Logical contiguous strings (`char *line`). |
| **`srcs/parsing/`** | Structural Compilation | `char *line` | Evaluated, syntactically-pristine `t_ast *` tree. |
| **`srcs/exec/`** | Physical OS Translation | `t_ast *root` | `fork`s, `/tmp/` files, and `0-255` exit statuses. |
| **`srcs/state/`** | Memory & Signal Context | `state->envp` matrices | Protected Global mappings (`g_last_signal`). |

---

## 🧠 **Global State Strategy**
Minishell relies on `t_shell_state` acting as a localized "Singleton" passed explicitly through the entire pipeline. 
- **Read-Only Topologies:** `input` and `parsing` strictly read from state (e.g., verifying `$HOME` exists). 
- **Mutable Overwrites:** Only `exec` (specifically via builtins like `export` and `cd`) physically destroys and recreates inner matrices like `$PWD`.
- **Interrupts:** `g_last_signal` forms the exclusive bridge between asynchronous hardware interrupts (`Ctrl+C`) and the synchronous synchronous command loop.

---

## 🛡️ **Error & Signal Philosophy**
> [!IMPORTANT]
> **Crash Early, Free Aggressively:** The pipeline operates under strict failure bounds. If the `tokenizer` flags a syntax error, memory is immediately rolled back and the prompt returns without ever touching the AST. 

> [!CAUTION]
> **Signal Context Shifting:** Signal behavior rotates dynamically depending on the active component. An interactive `readline` captures `SIGINT` to clear the prompt. A running external binary (`cat`) strictly `SIG_IGN`s the parent terminal while the child inherits default interrupt kills.

---

## 🗂️ **Project Layout & Documentation Mapping**

For deep-dive technical documentation on specifically how memory boundaries and Posix limits are enforced natively, consult the hierarchical Subsystem Manifests:

- [srcs/README.md](srcs/README.md) — High-level API Map.
- [includes/README.md](includes/README.md) — Header boundaries.
- [srcs/input/README.md](srcs/input/README.md) — Multiline parsing matrices.
- [srcs/parsing/README.md](srcs/parsing/README.md) — AST builder and Glob matcher logic.
- [srcs/exec/README.md](srcs/exec/README.md) — Heredoc spools and Execution drivers.
- [srcs/state/README.md](srcs/state/README.md) — Signal mutation laws.

---

## ⚙️ **Build**

Prerequisites:
- `cc`, `make`, `readline` and its development headers.

Build from the repository root:
```bash
make
```

**Useful targets:**
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

Run one command non-interactively with `-c`:
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
python3 minishell_tester2/main.py
```

For memory checking, Valgrind is incredibly useful alongside this structured architecture:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./minishell
```

---

## 🛠️ **Development Notes & Next Steps**

- Keep helper functions `static` when they are local to one translation unit.
- Treat ownership clearly for allocated strings and lists.
- Keep the pipeline readable: reader -> parser -> executor should stay easy to follow.
- **Potential Upgrades:** Extend the grammar further, add job control, and keep reducing unnecessary exported symbols across modules.
