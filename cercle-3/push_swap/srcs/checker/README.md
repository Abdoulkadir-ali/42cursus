# Checker Module

This directory contains the standalone checker program for the project. In the
current `push_swap` flow, this package is the validation layer: instead of
generating instructions, it reads instructions from standard input, executes
them on the provided stack state, and reports whether the final result is
correct.

The implementation here is contained in a single file, but it still performs
several distinct jobs:

- initialize the checker stack state from program arguments
- read instructions line by line from standard input
- dispatch each instruction through the project execution layer
- stop immediately on invalid input and clean up resources
- print `OK` or `KO` depending on the final stack state

## Entry Path

`main` in `checker.c` is the public entry point of the checker program.

The full flow is:

1. Return immediately if no values were provided.
2. Initialize the stacks from `argv + 1`.
3. Disable verbose output by default.
4. Print the initial debug state when debugging is enabled.
5. Process instructions from standard input.
6. Stop with status `1` if instruction processing reports an error.
7. Print the final checker result.
8. Free all stack resources.

This function acts as the coordinator for the checker runtime: it prepares the
initial state, delegates instruction reading, then validates the final result.

## Instruction Processing Path

`process_instructions` in `checker.c` is the main loop of the checker.

The steps are:

1. Read the first line from file descriptor `0` with `get_next_line`.
2. Continue while a line exists and is not just a newline.
3. Pass the instruction to `execute_instruction`.
4. Stop immediately if the instruction is invalid.
5. Print the intermediate debug state after each valid instruction.
6. Free the processed line.
7. Read the next instruction.
8. Free the final line if one remains.
9. Return `0` on success or `1` on failure.

This means the checker treats stdin as a stream of textual instructions and
applies them in order to the current stacks.

## Error Path

`handle_error` in `checker.c` centralizes the cleanup path when an invalid
instruction is encountered.

The steps are:

1. Print `Error\n` to the error output helper.
2. Free the current line buffer.
3. Free the stack state.
4. Return `1` to signal failure.

This keeps the main instruction loop simple and ensures that invalid input does
not leak memory.

## Output Path

`print_output` in `checker.c` is responsible for the final user-visible result.

The rule is simple:

- print `OK` if stack `a` is sorted and stack `b` is empty
- otherwise print `KO`

When `DEBUG` is enabled, the function also turns on verbose mode and prints the
final stack state through `debug_stacks`.

This makes the checker useful both as a strict validator and as a debugging
tool during development.

## Dependency Role

This file depends on several project subsystems:

- parsing and stack initialization through `init_stacks`
- instruction execution through `execute_instruction`
- sortedness validation through `is_sorted`
- cleanup through `free_stacks`
- optional debugging through `debug_line_stacks` and `debug_stacks`

So even though this folder contains only one file, it sits on top of several
core runtime modules.

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `main` -> `init_stacks` -> `process_instructions` -> `print_output`
2. `process_instructions` -> `get_next_line` -> `execute_instruction`
3. Invalid instruction path -> `handle_error`
4. Final result path -> `is_sorted` -> `write`

## Practical Role In The Project

The checker module is the verification side of the project. The `push_swap`
program tries to produce a good instruction sequence, while the checker asks a
different question: if this sequence is executed, does it actually sort the
stack correctly?

That makes this package essential for testing, debugging, and validating the
behavior of the rest of the codebase.