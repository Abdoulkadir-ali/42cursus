# Moves Module

This directory contains the primitive stack operations used by the whole
project. In the current `push_swap` flow, this package is the instruction
execution layer: parsing, checker logic, and the sorting algorithm all depend
on these functions to perform the legal stack transformations required by the
subject.

The implementation here is split across the four move families:

- `push.c` handles `pa` and `pb`
- `rotate.c` handles `ra`, `rb`, and `rr`
- `reverse_rotate.c` handles `rra`, `rrb`, and `rrr`
- `swap.c` handles `sa`, `sb`, and `ss`

## Data Structure Constraint

All operations in this folder work on the project's circular linked-list stack
representation.

That matters because:

- rotating forward can be done by moving the head pointer to `next`
- reverse rotating can be done by moving the head pointer to the last node
- push and swap operations must preserve the circular links

This is why the code often updates the head pointer directly instead of moving
through a null-terminated list.

## Push Path

`push` in `push.c` is the shared internal helper behind `pa` and `pb`.

The full flow is:

1. Remove the top node from the source stack with `pop_from_stack`.
2. Stop and return `0` if the source stack is empty.
3. Insert the removed node at the top of the destination stack with `push_to_stack`.
4. Return `1` on success.

`pa` and `pb` then wrap that helper and print the corresponding instruction
name when verbose mode is enabled.

## Pop Path

`pop_from_stack` in `push.c` removes the current head from a circular stack.

The steps are:

1. Return `NULL` if the stack pointer or stack is empty.
2. Store the current head.
3. If the stack has one element, set the stack to `NULL`.
4. Otherwise find the last node with `ft_last`.
5. Move the head pointer to the next node.
6. Reconnect the last node to the new head.
7. Detach the removed node by setting its `next` pointer to `NULL`.

This helper converts one node from circular-list ownership into a standalone
node ready to be inserted elsewhere.

## Push-To-Top Path

`push_to_stack` in `push.c` inserts one node as the new head of a destination
stack.

The steps are:

1. If the destination is empty, make the node point to itself and store it as the head.
2. Otherwise find the current last node.
3. Link the new node to the current head.
4. Link the old last node to the new node.
5. Replace the stack head with the new node.

This preserves the circular structure while making the pushed node the new top.

## Forward Rotation Path

`rotate` in `rotate.c` is the internal helper behind `ra` and `rb`.

The rule is simple:

- if the stack is empty, return `0`
- if the stack has fewer than two nodes, return `1` without changing it
- otherwise move the head pointer to `next`

Because the list is circular, this single pointer update is enough to rotate
the stack forward.

`ra`, `rb`, and `rr` then expose the public operations and print instruction
names when verbose mode is active.

## Reverse Rotation Path

`reverse_rotate` in `reverse_rotate.c` is the internal helper behind `rra` and
`rrb`.

The steps are:

1. Return `0` if the stack is empty.
2. Return `1` unchanged for stacks with fewer than two nodes.
3. Move the head pointer to the last node using `ft_last`.

This performs the inverse of `rotate`: the previous tail becomes the new head.

`rra`, `rrb`, and `rrr` then wrap the helper and emit the matching instruction
names when verbose output is enabled.

## Swap Path

`swap` in `swap.c` is the internal helper behind `sa` and `sb`.

The full flow is:

1. Return `0` if the stack is empty.
2. Return `1` unchanged if the stack has only one node.
3. Store the first two nodes.
4. If the stack has exactly two nodes, just move the head to the second node.
5. Otherwise find the last node.
6. Relink the first two nodes in reversed order.
7. Reconnect the last node to the new head.
8. Replace the stack head with the second node.

This operation swaps only the top two elements while preserving the rest of the
list order.

## Combined Operations Path

The combined public operations in this folder are:

- `rr`: rotate both stacks
- `rrr`: reverse rotate both stacks
- `ss`: swap both stacks

These wrappers call the underlying per-stack helpers and then print only the
combined instruction name when verbose mode is active.

That behavior matters because the output instruction stream must match the
allowed push_swap command set exactly.

## Output Behavior

Every public operation checks the `verbose` field in `t_stacks` before printing
its instruction name.

This means the same move functions can be used in two modes:

- silent internal execution
- visible instruction output for the final program or debug traces

The checker and debugging flows rely on that distinction.

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `pa` or `pb` -> `push` -> `pop_from_stack` -> `push_to_stack`
2. `ra`, `rb`, or `rr` -> `rotate`
3. `rra`, `rrb`, or `rrr` -> `reverse_rotate` -> `ft_last`
4. `sa`, `sb`, or `ss` -> `swap` -> `ft_last`

## Practical Role In The Project

The moves module is the mechanical foundation of the project. The algorithm can
choose targets and compute costs, but every real stack transformation still
passes through the functions in this folder.

That makes this package one of the most central parts of the codebase: it is
the layer where abstract sorting decisions become the exact legal instructions
defined by the subject.