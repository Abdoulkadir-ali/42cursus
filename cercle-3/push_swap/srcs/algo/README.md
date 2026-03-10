# Algorithm Package

This directory contains the orchestration layer of the `push_swap` sorting
engine. In the current project flow, this package sits above the lower-level
stack operations and below the program entry point: it coordinates target
selection, cost evaluation, move execution, and final stack normalization until
the full sorting process is complete.

The implementation here is split between top-level control files and focused
subpackages:

- `push_swap.c` drives the global sorting flow
- `moves.c` executes the return moves from stack `b` into stack `a`
- `cost/` computes move costs and cheapest candidates
- `sort/` handles sorted checks, small cases, and the forward reduction phase
- `target/` selects insertion targets in the opposite stack

## Package Role

The algorithm package is responsible for turning primitive stack operations into
a complete strategy.

At a high level, it does three things:

1. reduce stack `a` by pushing carefully chosen nodes into stack `b`
2. rebuild stack `a` by moving nodes back from `b` with target-aware alignment
3. rotate the final result so the stack starts at the correct extreme value

This means the package does not just perform moves. It decides when to compute
metadata, when to choose candidates, and when to execute each phase of the
sorting pipeline.

## Index Initialization Path

`init_indices` in `push_swap.c` prepares metadata before cost or target logic
can run.

The steps are:

1. Start from the head of the given stack.
2. Assign a sequential index to each node.
3. Mark whether each node is above the median of the stack.
4. Continue until the requested length is covered.

This metadata is reused throughout the package. Cost calculation, target
selection, and move alignment all depend on it.

## Main Entry Path

`push_swap` in `push_swap.c` is the public entry point for the full sorting
algorithm.

The full flow is:

1. Return immediately if stack `a` is already sorted.
2. Handle the two-element case directly with `sa` when needed.
3. Handle the three-element case directly with `sort_three`.
4. Call `turk_algorithm` for the front half of the strategy.
5. Process stack `b` until all nodes are moved back into `a`.
6. Finalize stack `a` so the extreme node becomes the visible head.

This function is the package coordinator: it does not compute every detail
itself, but it decides which phase runs next and when the algorithm is done.

## Return Phase Path

`process_b_stack` in `push_swap.c` handles the second half of the algorithm,
where nodes are moved back from stack `b` into stack `a`.

The steps are:

1. Continue while stack `b` is not empty.
2. Recompute lengths and indexes for both stacks.
3. Assign return targets with `set_b_targets`.
4. Compute the cost of moving each node in stack `b`.
5. Mark the cheapest node with `set_cheapest_node`.
6. Scan for that marked node.
7. Execute the selected move with `execute_moves`.

This loop is the package-level mirror of the forward reduction logic performed
earlier by the sort module.

## Final Alignment Path

`finalize_a_stack` in `push_swap.c` performs the last normalization step after
all nodes are back in stack `a`.

The steps are:

1. Return immediately if stack `a` is empty.
2. Recompute indexes for the full stack.
3. Find the extreme node with `find_extreme`.
4. Rotate upward or downward until that node becomes the head.

This matters because a stack can be circularly ordered but still not start at
the correct visible position. The final rotations fix that last detail.

## Move Execution Path

`execute_moves` in `moves.c` performs the actual return move for the node chosen
from stack `b`.

The full flow is:

1. Read the metadata of the chosen node and its target.
2. Apply shared rotations with `rotate_both` when both nodes move in the same direction.
3. Finish aligning stack `b` with `prep_for_push`.
4. Finish aligning stack `a` with `prep_for_push`.
5. Push the selected node back into stack `a` with `pa`.

This file owns the transition from metadata decisions to real instructions.

## Shared Rotation Path

`rotate_both` in `moves.c` handles the combined rotation cases used during the
return phase.

The rule is simple:

- if both nodes are above the median, use `rr`
- if both nodes are below the median, use `rrr`

Combined rotations reduce the total instruction count before the individual
stack alignment helpers finish the job.

## Single-Stack Preparation Path

`prep_for_push` in `moves.c` aligns one stack at a time before `pa` is called.

The steps are:

1. Choose which stack to prepare from the `stack` argument.
2. Rotate until the requested node reaches the top.
3. Use forward or reverse rotations depending on `above_median`.

This helper is used for both stack `a` and stack `b`, which keeps the move code
compact while preserving the exact execution order.

## Subpackage Responsibilities

The subdirectories in this package split the algorithm into focused roles:

- `cost/` decides how expensive each move is
- `sort/` performs the front-half reduction and small-case sorting
- `target/` decides where each node should be inserted

The top-level files then tie those decisions together into one continuous
sorting process.

## Folder-Level Call Chains

The main function chains in this package are:

1. `push_swap` -> `turk_algorithm` -> forward reduction in `sort/`
2. `push_swap` -> `process_b_stack` -> `set_b_targets` -> `calculate_cost` -> `set_cheapest_node` -> `execute_moves`
3. `execute_moves` -> `rotate_both` -> `prep_for_push` -> `pa`
4. `push_swap` -> `finalize_a_stack` -> `find_extreme`

## Practical Role In The Project

This package is the core of the project. Parsing prepares the initial stack,
primitive operations provide the legal instruction set, but the algorithm layer
is what turns those pieces into an optimized sorting process.

That is why the folder sits at the center of the runtime architecture: it
combines target logic, cost logic, and move logic into a full decision-making
pipeline rather than a collection of isolated helpers.