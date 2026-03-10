# Cost Module

This directory contains the code that estimates how expensive each candidate
move is during the `push_swap` sorting process. In the current flow, this
package is the bridge between target selection and move execution: it converts
node positions into an operation cost so the algorithm can choose the cheapest
element to push next.

The implementation here is small, but it does several distinct jobs:

- initialize the context needed for a cost calculation
- compute the push cost from stack positions and target positions
- handle shared rotation cases to reduce total operations
- scan a stack and mark the cheapest node

## Cost Calculation Path

`calculate_cost` in `cost.c` is the main entry point for computing the cost of
moving one node.

The steps are:

1. Reject a null metadata pointer or a missing target immediately.
2. Select the source and target stack lengths depending on the move direction.
3. Initialize a `t_cost_ctx` structure with `init_cost_ctx`.
4. Compute the final push cost with `compute_push_cost`.

This function does not perform the move itself. It only prepares the cost value
stored in the node metadata so later parts of the algorithm can compare
candidates.

## Context Initialization Path

`init_cost_ctx` in `helper.c` prepares the values used by the final cost logic.

The steps are:

1. Read the target node metadata from `meta_a->target`.
2. Store both metadata pointers in the context.
3. Copy the current indexes into `cost_a` and `cost_b`.
4. Store the source and target stack lengths.

At this stage, no decision has been made about the cheapest move. The helper
only gathers the data required for the final calculation.

## Push Cost Path

`compute_push_cost` in `helper.c` applies the actual cost rules.

The result depends on whether the node and its target are above or below the
median of their respective stacks:

- if both are above the median, the cost is the larger of the two forward rotation counts
- if both are below the median, the cost is the larger of the two reverse rotation counts
- if one is above and the other is below, the costs are added separately

This matters because shared rotations such as `rr` or shared reverse rotations
such as `rrr` can reduce the total number of operations when both nodes move in
the same direction.

## Cheapest Node Selection

`set_cheapest_node` in `cost.c` is responsible for choosing the best candidate
after all relevant nodes already have a computed `push_cost`.

The full flow is:

1. Return immediately if the stack is empty.
2. Initialize the current cheapest node and the minimum cost.
3. Call `scan_for_cheapest` to walk through the stack.
4. Reset every node's `is_cheapest` flag during the scan.
5. Keep the node with the smallest `push_cost`.
6. Mark that node as the cheapest choice.

This gives the sorting algorithm one clear next move to execute.

## Supporting Helper

`max_val` in `helper.c` is a small utility used by the shared-rotation cases.

Its role is simple:

- return the larger of two values

That behavior is important because when two rotations can be combined, the real
cost is determined by the longer of the two paths rather than by their sum.

## Memory And State Behavior

This directory does not allocate dynamic memory directly. Its job is to read
stack metadata, compute numeric costs, and write the result back into the node
state.

That makes this module a pure decision layer inside the algorithm: it updates
metadata without changing the actual stack topology.

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `calculate_cost` -> `init_cost_ctx` -> `compute_push_cost`
2. `set_cheapest_node` -> `scan_for_cheapest`
3. `compute_push_cost` -> `max_val`

## Practical Role In The Algorithm

The cost module is what lets the project move from “possible move” to “best
move”. Without it, the algorithm could still find targets, but it would not
have a reliable way to compare candidates and minimize the total operation
count.

That tradeoff keeps responsibilities clear: target code decides where a node
should go, cost code decides how expensive it is to get there, and move code
executes the result.