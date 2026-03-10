# Parsing Package

This directory contains the parsing layer of the project. In the current
`push_swap` flow, this package is responsible for turning raw textual input
into validated runtime state, and for turning textual checker instructions into
calls to the primitive move functions.

The package is split into two focused subdirectories:

- `moves/` parses and dispatches checker instructions such as `sa`, `pb`, or `rrr`
- `stacks/` validates numeric input and builds the initial stack structures

## Package Role

The parsing package handles two different kinds of text input:

1. the integer values passed on the command line
2. the textual instructions read by the checker from standard input

That means this package sits at two important boundaries of the program:

- startup, where arguments must become a valid stack
- validation, where raw instruction strings must become legal operations

## Stack Parsing Path

The `stacks/` subpackage is responsible for input validation and stack
construction.

Its main responsibilities are:

- split argument strings into tokens
- parse integers safely with overflow checks
- reject invalid numeric forms
- reject duplicate values
- build the circular stack structure
- clear partially built state on failure

This is the package used by both `push_swap` and the checker when they build
their initial stack state from command-line arguments.

## Instruction Parsing Path

The `moves/` subpackage is responsible for checker instruction dispatch.

Its responsibilities are:

- compare one input line against the allowed instruction set
- call the matching move function
- reject unknown instructions

This means the checker can stay focused on reading lines and validating the
final result, while the actual instruction decoding stays isolated here.

## Dependency Role

This package depends on several lower-level systems:

- list helpers for node creation and cleanup
- stack helpers for full stack cleanup
- primitive move functions for checker instruction execution
- libft helpers such as `ft_split`, `ft_strcmp`, and digit checks

At the same time, higher-level modules depend on parsing to create valid input
state before any algorithm or checker logic can run.

## Folder-Level Call Chains

The main function chains in this package are:

1. stack creation path -> `init_stacks` -> `process_string` -> `add_numbers_from_split` -> `parse_int`
2. duplicate validation path -> `add_numbers_from_split` -> `is_duplicate`
3. checker instruction path -> `execute_instruction` -> operation-specific dispatch helpers

## Practical Role In The Project

The parsing package is the gatekeeper of correctness. If raw inputs are not
validated here, the rest of the codebase cannot rely on the stack state or the
checker instruction stream.

That makes this package foundational even though it does not sort anything by
itself: it ensures that everything entering the runtime is structurally valid
before the algorithm or checker begins.