# 🧭 **Source Pipeline** - *How push_swap moves from input to sorted stack*

> **A high-level map of the `srcs/` tree.**  
> This README explains how the source folders fit together in the global
> `push_swap` runtime, from argument parsing and stack construction to cost-
> based sorting, instruction execution, and checker validation.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Scope](https://img.shields.io/badge/Scope-srcs%2F-overview-1f6feb?style=for-the-badge)
![Architecture](https://img.shields.io/badge/Architecture-pipeline-success?style=for-the-badge)

---

## 📖 **Overview**

The `srcs/` directory is the operational heart of the project. It contains the
runtime code that turns raw integer input into either:

1. a valid sorting instruction sequence through `push_swap`
2. a correctness verdict through `checker`

At a high level, the project behaves like this:

```text
main -> parsing -> algo -> moves
			 |          ^       |
			 v          |       v
		 helper <------|---- checker
```

`helper/` supports every stage, while `moves/` acts as the shared execution
layer used both by the sorting algorithm and by checker-side instruction
validation.

---

## 🚀 **Global Pipeline**

The full runtime pipeline across `srcs/` is:

1. `main/` receives command-line arguments for the `push_swap` binary.
2. `parsing/stacks/` validates numeric input, rejects duplicates, and builds stack `a`.
3. `helper/lst/` stores values in the project’s circular linked-list stack model.
4. `algo/sort/` performs the forward reduction phase from stack `a` to stack `b`.
5. `algo/target/` chooses insertion targets in the opposite stack.
6. `algo/cost/` computes the cost of each candidate move.
7. `algo/` selects the cheapest node and coordinates the remaining algorithm flow.
8. `moves/` performs the legal stack instructions that mutate the runtime state.
9. `helper/` provides cleanup, stack display, and shared error-output helpers.
10. `checker/` reuses parsing and move execution to validate an instruction stream against the same runtime rules.

---

## 🗂️ **Top-Level Folders**

### `main/`

The entry layer of the `push_swap` program.

- receives user arguments
- supports both quoted and split input forms
- initializes the main stack state
- launches the sorting algorithm
- frees the runtime state before exit

In the global flow, `main/` is the startup bridge into the rest of the codebase.

### `parsing/`

The input construction and instruction-decoding layer.

- `stacks/` validates integers, rejects duplicates, and builds stacks
- `moves/` decodes checker instructions such as `sa`, `pb`, or `rrr`

In the global flow, `parsing/` converts text into valid runtime data or legal operations.

### `algo/`

The decision-making layer of the project.

- `sort/` handles sorted checks, small cases, and the front-half reduction phase
- `target/` decides where nodes should be inserted
- `cost/` estimates how expensive each move is
- top-level files coordinate the full sorting strategy

In the global flow, `algo/` turns stack state into move decisions.

### `moves/`

The primitive instruction execution layer.

- implements push, swap, rotate, and reverse-rotate operations
- exposes the exact legal instruction set of the subject
- supports both visible instruction output and silent internal execution

In the global flow, `moves/` is where algorithm choices become real stack mutations.

### `checker/`

The validation layer.

- initializes stack state from input
- reads instructions from standard input
- executes them through the shared move layer
- reports `OK`, `KO`, or `Error`

In the global flow, `checker/` replays a move sequence instead of generating one.

### `helper/`

The shared support layer.

- `lst/` manages the circular linked-list stack structure
- `display/` handles shared error-output helpers

In the global flow, `helper/` provides the low-level support code used by every major stage.

---

## 🔄 **Typical Runtime Journey**

For a normal `push_swap` run, the trip through `srcs/` looks like this:

1. `main/main.c` starts the program.
2. `parsing/stacks/` turns the arguments into validated stack nodes.
3. `algo/sort/` pushes part of stack `a` into stack `b`.
4. `algo/target/` and `algo/cost/` prepare insertion targets and move costs.
5. `algo/push_swap.c` and `algo/moves.c` choose and coordinate the best next move.
6. `moves/` applies the corresponding instruction sequence.
7. Final rotations normalize stack `a`.
8. `helper/` supports cleanup and optional debug output.

For a normal `checker` run, the journey is different:

1. `checker/checker.c` initializes the stacks from arguments.
2. `parsing/moves/parser.c` decodes each textual instruction.
3. `moves/` applies the instruction to the current state.
4. `algo/sort/` contributes the final sortedness check.
5. `checker/` prints `OK` or `KO`.

---

## 🧩 **How the Folders Depend on Each Other**

- `main/` depends on `parsing/`, `algo/`, and `helper/` directly.
- `parsing/` depends on `helper/lst/` for node construction and cleanup.
- `algo/` depends on `moves/` to execute the chosen strategy.
- `algo/` also depends on `helper/` and parsing-built stack state.
- `checker/` depends on `parsing/`, `moves/`, `algo/sort/`, and `helper/`.
- `helper/` provides the shared low-level infrastructure used across the full runtime.

This is why the tree feels linear at first glance, but behaves more like a loop
between state analysis and state mutation:

```text
parse -> analyze targets -> compute cost -> execute move -> analyze again
```

---

## 🛠️ **Reading Guide**

If you want to understand the project from top to bottom, read the folders in
this order:

1. `main/`
2. `parsing/`
3. `helper/lst/`
4. `moves/`
5. `algo/sort/`
6. `algo/target/`
7. `algo/cost/`
8. `algo/`
9. `checker/`

That order follows the same mental model as the actual runtime flow.

---

## 📚 **Submodule READMEs**

For the detailed function-oriented breakdowns, continue with:

- [srcs/algo/README.md](srcs/algo/README.md)
- [srcs/checker/README.md](srcs/checker/README.md)
- [srcs/helper/README.md](srcs/helper/README.md)
- [srcs/main/README.md](srcs/main/README.md)
- [srcs/moves/README.md](srcs/moves/README.md)
- [srcs/parsing/README.md](srcs/parsing/README.md)

This file stays intentionally high-level so the rest of the `srcs/` READMEs can
go deeper into each stage.
