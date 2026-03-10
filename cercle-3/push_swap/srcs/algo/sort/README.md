# Sort Module

This directory contains the code that drives the high-level sorting flow for
`push_swap`. In the current algorithm, this package is the layer that decides
when the stack is already ordered, handles very small stack cases directly, and
coordinates the main `a -> b` phase before the final reconstruction steps.

The implementation here is compact, but it does several distinct jobs:

- compare values according to the configured order
- detect whether a stack is already sorted
- sort the special case of exactly three elements
- push candidates from stack `a` to stack `b` using cost-based selection
- perform the opening phase of the Turk sorting strategy

## Comparison Path

`cmp` in `sort.c` is the smallest helper in this directory, but it defines the
ordering rule used by `is_sorted`.

The result depends on the `ASCENDING` macro:

- if `ASCENDING` is enabled, it checks `a <= b`
- otherwise, it checks `a >= b`

This keeps the sortedness test configurable without duplicating the traversal
logic.

## Sortedness Check Path

`is_sorted` in `sort.c` is the entry point for verifying whether a stack is
already ordered.

The steps are:

1. Return `1` immediately for an empty stack.
2. Return `1` for a stack of size `0` or `1`.
3. Start from the first node and walk through the list.
4. Compare each pair of consecutive values with `cmp`.
5. Return `0` on the first ordering failure.
6. Return `1` if the full traversal succeeds.

This function is used as a cheap correctness check before or after parts of the
algorithm manipulate the stacks.

## Three-Element Sort Path

`sort_three` in `sort.c` handles the smallest non-trivial stack directly.

The function reads the first three values from stack `a` into a local context
and applies a small set of hard-coded cases.

The full flow is:

1. Read the top three values from stack `a`.
2. Compare them against the known order patterns.
3. Apply the minimum matching operation sequence.

The function uses only the basic operations:

- `sa`
- `ra`
- `rra`

This avoids invoking the heavier algorithm machinery for a case that can be
solved with a small number of direct rules.

## A-To-B Processing Path

`process_a_to_b` in `sort.c` is the loop that keeps moving candidates from
stack `a` into stack `b` until only the small base case remains.

The steps are:

1. Continue while stack `a` has more than three nodes.
2. Recompute indexes for both stacks.
3. Assign target nodes with `set_target_nodes`.
4. Walk through stack `a` and calculate the push cost for each node.
5. Select the cheapest candidate with `find_cheapest`.
6. Execute the move with `move_a_to_b`.

This is the main reduction loop of the sort package: it turns a large unsorted
stack into a smaller core that can be finished with direct rules.

## Turk Algorithm Opening Path

`turk_algorithm` in `sort.c` prepares the initial state before the repeated
cost-based processing begins.

The full flow is:

1. Read the initial size of stack `a`.
2. Return immediately for sizes of three or less.
3. Push one element to `b` if the size is above three.
4. Push a second element to `b` if the size is above four.
5. Swap the top of `b` when needed to keep that stack better arranged.
6. Call `process_a_to_b` for the main reduction phase.
7. Finish the remaining two- or three-element case in stack `a`.

This function does not complete the whole project alone. Its role is to set up
and run the front half of the sorting strategy so later stages can restore the
remaining elements efficiently.

## Shared Rotation Path

`move_a_to_b` in `helper.c` executes the selected move after the cheapest node
has already been chosen.

Its flow is:

1. Reject a null node or missing target.
2. Rotate both stacks together when both nodes move in the same direction.
3. Finish aligning stack `a` with `rotate_a`.
4. Finish aligning stack `b` with `rotate_b`.
5. Push the selected node from `a` to `b` with `pb`.

The shared-rotation step matters because combined operations such as `rr` and
`rrr` reduce the total instruction count.

## Stack Alignment Helpers

The static helpers in `helper.c` split the move execution into focused steps:

- `rotate_both` handles shared `rr` and `rrr` cases
- `rotate_a` finishes aligning the chosen node in stack `a`
- `rotate_b` finishes aligning the target node in stack `b`

This keeps `move_a_to_b` short while preserving the exact order of operations.

## Cheapest Lookup Path

`find_cheapest` in `helper.c` scans a stack and returns the node with the
smallest `push_cost`.

The steps are:

1. Initialize the current cheapest pointer to `NULL`.
2. Initialize the minimum cost to `LONG_MAX`.
3. Walk through the full stack.
4. Replace the current cheapest pointer whenever a lower cost is found.
5. Return the final cheapest node.

This helper does not mark metadata flags itself. It only returns the node that
should be used by the next move.

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `is_sorted` -> `cmp`
2. `turk_algorithm` -> `process_a_to_b` -> `calculate_cost` -> `find_cheapest` -> `move_a_to_b`
3. `move_a_to_b` -> `rotate_both` -> `rotate_a` -> `rotate_b` -> `pb`
4. Final small-case handling -> `sort_three` or `sa`

## Practical Role In The Algorithm

The sort module is the control layer that turns lower-level helpers into an
actual strategy. Target code decides where nodes should go, cost code decides
which candidate is cheapest, and this package decides when to apply those
decisions and how to reduce the problem toward a trivial end state.

That tradeoff keeps the project modular: this directory owns the sorting flow,
while the surrounding modules provide the information and primitive operations
it needs.