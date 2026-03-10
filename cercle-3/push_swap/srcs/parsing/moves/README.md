# Instruction Parsing Module

This directory contains the code that turns checker input lines into actual
stack operations. In the current project flow, this package is the bridge
between textual instructions read from standard input and the primitive move
functions that mutate the stack state.

The implementation here is contained in a single file, but it still performs
several distinct jobs:

- recognize swap instructions
- recognize push instructions
- recognize rotate instructions
- recognize reverse-rotate instructions
- reject unknown commands cleanly

## Entry Path

`execute_instruction` in `parser.c` is the public entry point for instruction
dispatch.

The full flow is:

1. Try to match the line against the swap family.
2. If no swap matched, try the push family.
3. If no push matched, try the rotate family.
4. Return `0` if no valid instruction matched.
5. Return `1` as soon as one family handles the line.

This function does not read from stdin itself. It only receives one already
read instruction string and decides whether it maps to a legal project
operation.

## Swap Dispatch Path

`execute_swap` in `parser.c` handles the swap-family instructions.

The accepted lines are:

- `sa\n`
- `sb\n`
- `ss\n`

The steps are:

1. Compare the input line against each valid swap instruction.
2. Call the corresponding move function when a match is found.
3. Return `1` on success or `0` if the family does not match.

## Push Dispatch Path

`execute_push` in `parser.c` handles the push-family instructions.

The accepted lines are:

- `pa\n`
- `pb\n`

Its control flow is the same as the swap dispatcher: compare, execute, return a
success flag.

## Rotate Dispatch Path

`execute_rotate` in `parser.c` handles the rotate-family instructions.

The accepted lines are:

- `ra\n`
- `rb\n`
- `rr\n`

If none of those match, the function falls back to `execute_reverse_rotate`.

That means the rotate path also acts as the handoff point to the reverse-rotate
family.

## Reverse-Rotate Dispatch Path

`execute_reverse_rotate` in `parser.c` handles the remaining instruction family.

The accepted lines are:

- `rra\n`
- `rrb\n`
- `rrr\n`

If none of those match either, the function returns `0`, which bubbles all the
way back to `execute_instruction` and tells the caller that the input line is
invalid.

## Practical Limitation

The parser is intentionally strict: it matches exact strings including the
newline character.

That means:

- only the official instruction names are accepted
- unexpected characters or malformed spacing cause rejection
- instruction validation is deterministic and simple

This matches the project scope: the checker does not need a flexible command
language, only a precise decoder for the legal move set.

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `execute_instruction` -> `execute_swap`
2. `execute_instruction` -> `execute_push`
3. `execute_instruction` -> `execute_rotate` -> `execute_reverse_rotate`

## Practical Role In The Project

This module is the decoding layer for checker execution. The checker reads
lines, but this file is what gives those lines meaning by translating them into
the legal primitive operations used everywhere else in the project.