# 🧩 **Public Headers** - *The API surface of minishell*

> **A guide to the `includes/` directory.**  
> These headers define the shared types, function prototypes, and subsystem
> boundaries used across the shell.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Scope](https://img.shields.io/badge/Scope-includes%2F-1f6feb?style=for-the-badge)
![Role](https://img.shields.io/badge/Role-public%20API-success?style=for-the-badge)

---

## 📖 **Overview**

The `includes/` directory is the contract layer of the project. While `srcs/`
contains the implementations, these headers define how the modules talk to each
other.

At a high level, the headers mirror the same architecture as the runtime code:

```text
core -> input -> parsing -> exec
          ^                    |
          |                    v
        state <----------------+
             \
              -> lib
```

Each header groups one subsystem's exported types and functions so the codebase
can stay modular without turning into one giant shared namespace.

---

## 🗂️ **Header Map**

### `core.h`

The top-level shell entry header.

- Includes the major subsystem headers.
- Exposes the public entry points `main` and `minishell`.
- Acts as the narrow bridge between the executable entry and the rest of the project.

In the project pipeline, `core.h` sits at the top and pulls the major pieces
together.

### `input.h`

The command acquisition and preprocessing header.

- Declares the input pipeline entry points such as `get_command_line` and `process_input`.
- Exposes the multiline reader and extender helpers.
- Defines the small helper structs used by the reader and continuation logic.

In the project pipeline, `input.h` connects raw user text to the parser-facing
stages.

### `parsing.h`

The largest transformation header in the project.

- Defines the core parsing data structures such as `t_token`, `t_ast`, and the expansion context structs.
- Declares tokenization, syntax validation, expansion, wildcard, and AST-building functions.
- Centralizes the parser-side enums and helper prototypes used across multiple parsing files.

In the project pipeline, `parsing.h` describes the full path from raw shell text
to structured command trees.

### `exec.h`

The execution-layer header.

- Defines execution-side helper structs such as builtin definitions, heredoc context, and export context.
- Declares the AST execution entry points, builtin dispatchers, heredoc helpers, and environment mutation helpers used during execution.
- Exposes the APIs that turn parsed command structures into actual shell behavior.

In the project pipeline, `exec.h` is where structured command data becomes
processes, redirections, builtins, and exit statuses.

### `state.h`

The runtime-state and signal-policy header.

- Defines `t_shell_state`, the shared runtime context carried through the shell.
- Exposes shell initialization, environment lookup, `SHLVL` setup, and signal mode switching.
- Declares `g_last_signal`, which bridges asynchronous signal events to later control flow.

In the project pipeline, `state.h` provides the persistent runtime context that
all other major modules depend on.

### `lib.h`

The shared utility header.

- Declares small support helpers that do not belong to a larger subsystem.
- Exposes formatted error printing and small matching helpers.
- Supports the rest of the codebase without acting as its own major pipeline stage.

In the project pipeline, `lib.h` is infrastructure rather than a main step.

---

## 🔄 **How the Headers Fit the Global Flow**

The runtime source pipeline has a matching header pipeline:

1. `core.h` starts the shell and pulls the subsystem APIs together.
2. `state.h` defines the runtime context created during startup.
3. `input.h` reads and prepares one logical command line.
4. `parsing.h` transforms that line into tokens, expansions, and an AST.
5. `exec.h` executes the AST and updates the shell-visible state.
6. `lib.h` provides shared utility support across multiple stages.

This means `includes/` is not just a folder of declarations. It is the project’s
high-level API map.

---

## 🧠 **Design Role of the Header Layer**

The header split is useful for three reasons:

1. it keeps subsystem boundaries explicit
2. it makes shared types visible in one predictable place
3. it reduces accidental coupling between unrelated implementation files

That separation matters especially in minishell, because the project mixes
parsing, process control, environment mutation, signal handling, and terminal
interaction inside one executable.

---

## 📚 **Reading Order**

If you want to understand the public API first, read the headers in this order:

1. `state.h`
2. `parsing.h`
3. `exec.h`
4. `input.h`
5. `core.h`
6. `lib.h`

That order gives you the data model first, then the pipeline, then the entry
point that ties it all together.

---

## 🔗 **Related Documentation**

For the implementation-side view of these APIs, continue with:

- [srcs/README.md](srcs/README.md)
- [srcs/core/README.md](srcs/core/README.md)
- [srcs/input/README.md](srcs/input/README.md)
- [srcs/parsing/README.md](srcs/parsing/README.md)
- [srcs/exec/README.md](srcs/exec/README.md)
- [srcs/state/README.md](srcs/state/README.md)

This README stays intentionally high-level so the source-tree READMEs can focus
on detailed control flow and function-level behavior.