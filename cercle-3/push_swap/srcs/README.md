# Source Package

This directory contains the full runtime implementation of the project. In the
current `push_swap` layout, `srcs/` is the main code package: it groups the
program entry point, the checker, the parsing layer, the primitive operations,
the helper utilities, and the sorting algorithm itself.

Each subdirectory owns one part of the runtime pipeline, and together they form
the complete flow from raw user input to a sorted stack or a validated checker
result.

## Package Role

At a high level, the code in `srcs/` is responsible for:

1. reading and validating integer input
2. building the circular stack structures
3. executing the legal stack operations
4. computing targets and costs for the algorithm
5. generating a sorting instruction sequence
6. validating instruction sequences through the checker

This means `srcs/` is not just a source folder in the generic sense. It is the
full runtime architecture of the project.

## Runtime Layout

The package is divided into six main runtime areas:

- `algo/` contains the sorting strategy and its orchestration
- `checker/` contains the standalone checker executable logic
- `helper/` contains shared utility code for errors, lists, and stack printing
- `main/` contains the `push_swap` entry point
- `moves/` contains the primitive legal stack operations
- `parsing/` contains input validation and instruction parsing

Each area has its own focused README so the documentation can stay close to the
implementation.

## Execution Flow

For the main `push_swap` binary, the flow through `srcs/` is:

1. `main/` receives command-line arguments.
2. `parsing/` validates and converts them into stack nodes.
3. `helper/lst/` stores them in the project’s circular list structure.
4. `algo/` computes targets, costs, and move order.
5. `moves/` executes the primitive stack operations.
6. `helper/` supports cleanup and shared output behavior.

For the `checker` binary, the flow is:

1. `checker/` initializes the stacks from arguments.
2. `parsing/moves/` decodes textual instructions.
3. `moves/` executes those instructions.
4. `algo/sort/` contributes the final sortedness check.
5. `helper/` supports output and cleanup.

## Architectural Notes

Two design choices shape most of the code in this tree:

- stacks are implemented as circular linked lists
- the sorting logic is based on targets, move costs, and cheapest-node
	selection rather than a fixed hard-coded sequence

The first choice affects how rotations, insertions, and list traversal work.
The second choice affects how the algorithm package is split into `target/`,
`cost/`, `sort/`, and the top-level orchestration files.

## Documentation Map

The main package-level READMEs inside `srcs/` are:

- `algo/README.md`
- `checker/README.md`
- `helper/README.md`
- `main/README.md`
- `moves/README.md`
- `parsing/README.md`

Subpackages also include their own focused documentation where needed, such as:

- `algo/cost/README.md`
- `algo/sort/README.md`
- `algo/target/README.md`
- `helper/display/README.md`
- `helper/lst/README.md`
- `parsing/moves/README.md`
- `parsing/stacks/README.md`

## Practical Role In The Project

If the root `README.md` explains what the project is, this file explains how
the implementation is organized. It is the entry point for navigating the code
inside `srcs/` and understanding which package owns which part of the runtime.

That makes `srcs/README.md` the bridge between the project overview and the
more detailed module-level documentation spread across the tree.
