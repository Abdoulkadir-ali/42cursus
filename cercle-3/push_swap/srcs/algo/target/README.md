# Target Module

This directory contains the code that decides where each node should be inserted
in the opposite stack. In the current `push_swap` flow, this package is the
bridge between raw stack state and cost calculation: before the algorithm can
measure how expensive a move is, it first needs to know which node is the
correct target.

The implementation here is small, but it does several distinct jobs:

- search stack `b` for the best insertion target of a node from stack `a`
- assign target nodes for every element in stack `a`
- assign return targets for every element in stack `b`
- find the extreme node used as a fallback target
- initialize the helper contexts used during these scans

## A-To-B Target Path

`find_target` in `target.c` is the main entry point for selecting the target of
one node from stack `a`.

The steps are:

1. Reset the node target to `NULL`.
2. Return immediately if stack `b` is empty.
3. Initialize a `t_target_ctx` with `init_target_ctx`.
4. Search stack `b` with `search_best_target`.
5. If no valid match exists, fall back to `find_max_node`.
6. Store the result in `node_a->meta.target`.

This function does not move anything. It only assigns the node in stack `b`
that should receive the current element from stack `a`.

## A-Stack Target Assignment Path

`set_target_nodes` in `target.c` applies `find_target` to the whole source
stack.

The steps are:

1. Return immediately if stack `a` is empty.
2. Start from the head of stack `a`.
3. Walk through every node.
4. Call `find_target` for each one.

This prepares all nodes in stack `a` for later cost computation.

## Target Search Logic

`init_target_ctx` in `helper.c` prepares the state used when searching inside
stack `b`.

The context stores:

- the current stack being scanned
- the current best target pointer
- the current scan pointer
- the scan size
- the best match value seen so far

The initial `best_match` depends on `ASCENDING`:

- in ascending mode, it starts at `INT_MIN`
- otherwise, it starts at `INT_MAX`

That setup allows `search_best_target` to keep only the closest valid match.

## Best Match Search Path

`search_best_target` in `helper.c` walks through stack `b` and updates the best
target candidate for one node from stack `a`.

The steps are:

1. Traverse the whole target stack.
2. Check whether the current node in `b` is a valid insertion match.
3. Compare it against the current best match.
4. Replace the stored target when a better candidate is found.
5. Continue until the scan is complete.

The exact comparisons depend on `cmp`, so the behavior stays consistent with
the project sorting order.

## Fallback Target Path

`find_max_node` in `target.c` is used when no regular insertion match is found
in stack `b`.

The steps are:

1. Return `NULL` if the stack is empty.
2. Initialize the first node as the current maximum.
3. Traverse the full stack.
4. Replace the stored node whenever a larger value is found.
5. Return the final maximum node.

This fallback is important because some values do not fit between existing
neighbors and need to wrap around the current ordering of stack `b`.

## Extreme Node Path

`find_extreme` in `target.c` is the generic helper used when the algorithm
needs the smallest or largest node in a stack, depending on the configured
ordering.

The steps are:

1. Return `NULL` if the stack is empty.
2. Initialize the extreme reference value from `ASCENDING`.
3. Traverse the full stack.
4. Keep the node that represents the current extreme.
5. Return that node.

This helper is reused when assigning targets for nodes coming back from stack
`b` into stack `a`.

## B-To-A Target Path

`set_b_targets` in `target.c` assigns the destination target in stack `a` for
every node currently in stack `b`.

The full flow is:

1. Initialize a `t_set_b_targets_ctx` with `init_b_targets_ctx`.
2. Walk through every node in stack `b`.
3. Call `find_target_for_b` for the current node.
4. Store the resulting target in the metadata.
5. Advance to the next node.

This path is used during the second half of the global algorithm, when elements
must be moved back into stack `a` in the correct order.

## B-Target Helper Path

`find_target_for_b` in `helper.c` searches stack `a` for the best insertion
point of the current node in stack `b`.

The steps are:

1. Reset the current target.
2. Initialize the best match sentinel depending on `ASCENDING`.
3. Start from the head of stack `a`.
4. Traverse the full stack and keep the closest valid match.
5. Fall back to `find_extreme` if no valid match exists.

This mirrors the `a -> b` search logic, but in the opposite direction.

## Context Initialization For B Targets

`init_b_targets_ctx` in `helper.c` prepares the context used by
`find_target_for_b`.

Its role is simple:

- store both stacks
- compute the size of stack `b`
- initialize the current node pointer for the outer scan

This keeps `set_b_targets` short and lets the search helper focus only on the
target-selection logic itself.

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `set_target_nodes` -> `find_target` -> `init_target_ctx` -> `search_best_target`
2. `find_target` -> fallback -> `find_max_node`
3. `set_b_targets` -> `init_b_targets_ctx` -> `find_target_for_b` -> fallback -> `find_extreme`

## Practical Role In The Algorithm

The target module is what gives meaning to every later move. Cost code cannot
measure a move until a destination exists, and move code cannot align stacks
until both the selected node and its target are known.

That is why this package sits near the center of the algorithm: it translates a
stack state into concrete insertion goals, and the rest of the sorting logic is
built on top of those decisions.