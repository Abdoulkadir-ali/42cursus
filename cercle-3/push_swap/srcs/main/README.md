# Main Module

This directory contains the main entry point of the `push_swap` program. In the
current project flow, this package is the startup layer: it receives command-
line arguments, prepares the initial stack state, launches the sorting
algorithm, and frees the runtime data before exiting.

The implementation here is contained in a single file, but it still performs
several distinct jobs:

- initialize the runtime stack container
- support both split argument forms accepted by the project
- validate that stack creation succeeded
- print debug snapshots around the sorting process
- call the main sorting algorithm
- release the full stack state before exiting

## Entry Path

`main` in `main.c` is the public entry point of the program.

The full flow is:

1. Initialize the stack structure with null pointers and default state.
2. Advance `argv` once so the code works directly with the user values.
3. Detect whether the program received a single quoted argument or multiple arguments.
4. If one quoted argument was provided, split it with `ft_split`.
5. Report `Error\n` and stop if splitting fails.
6. Build the stacks with `init_stacks`.
7. Free the temporary split array when that parsing path was used.
8. Report `Error\n` and stop if stack creation failed.
9. Print the initial debug snapshot.
10. Run the sorting algorithm with `push_swap`.
11. Print the final debug snapshot.
12. Free the stack state.
13. Return `0` on success.

This function is the top-level coordinator of the main program: it does not
implement parsing or sorting itself, but it wires those systems together in the
correct order.

## Single-Argument Parsing Path

When `argc == 2`, the program assumes the input may be given as one
space-separated string.

The steps are:

1. Read the single argument string.
2. Split it on spaces with `ft_split`.
3. Pass the resulting array to `init_stacks`.
4. Free the temporary array with `ft_free_split`.

This allows input forms such as:

- `./push_swap "3 2 1"`

instead of requiring every value to be passed as a separate shell argument.

## Multi-Argument Parsing Path

When `argc` is greater than `2`, the program uses the shifted `argv` array
directly.

This allows input forms such as:

- `./push_swap 3 2 1`

In this branch no temporary split array is created.

## Error Path

The entry file has two early failure checks:

- if `ft_split` fails, return `ft_puterr("Error\n")`
- if stack initialization leaves `stacks.a` empty, return `ft_puterr("Error\n")`

This means the program treats an invalid or unusable initial state as a direct
startup failure and stops before the algorithm begins.

## Debug Path

The function uses `debug_line_stacks` both before and after the call to
`push_swap`.

That gives the runtime two labeled snapshots:

- `Before state:`
- `After state:`

This is useful during development because it makes the full transformation of
the stacks visible around the main algorithm call.

## Dependency Role

This file sits on top of several core project subsystems:

- input preparation through `ft_split`
- stack initialization through `init_stacks`
- algorithm execution through `push_swap`
- debug output through `debug_line_stacks`
- cleanup through `free_stacks`
- error output through `ft_puterr`

So even though the folder contains only one source file, it acts as the entry
bridge into nearly the whole runtime.

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `main` -> `ft_split` -> `init_stacks` -> `ft_free_split`
2. `main` -> `init_stacks` -> `push_swap`
3. `main` -> `debug_line_stacks`
4. `main` -> `free_stacks`
5. Error path -> `ft_puterr`

## Practical Role In The Project

The main module is the user-facing startup point of `push_swap`. Parsing code,
algorithm code, and helper modules all do the real work, but this file decides
how the program enters that pipeline and when it exits.

That makes it small but central: it is the point where raw command-line input
becomes a fully initialized sorting run.