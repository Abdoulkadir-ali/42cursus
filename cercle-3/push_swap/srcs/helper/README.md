# Helper Package

This directory contains the shared utility layer used across the project. In
the current `push_swap` flow, this package groups the low-level helper code
that does not belong directly to parsing, algorithm control, or primitive move
execution, but still supports those systems at runtime.

The package is currently split into two focused subdirectories:

- `display/` handles error-output helpers
- `lst/` handles the circular stack-node container and stack printing helpers

## Package Role

The helper package provides the small reusable operations that other modules
build on top of.

At a high level, it covers two kinds of support code:

1. generic node-list management for the custom circular stack structure
2. small output helpers shared by runtime error paths and debugging flows

This keeps low-level utility logic out of the higher-level packages while still
making it available everywhere it is needed.

## Display Helper Role

The `display/` subpackage currently contains the error-output helper layer.

Its responsibilities are:

- print an error message to standard error
- optionally terminate the process after reporting an error

This gives parsing and startup code a short, consistent failure-reporting path.

## List Helper Role

The `lst/` subpackage contains the custom circular linked-list helpers used to
store stack nodes.

Its responsibilities are:

- create new nodes
- insert nodes at the front or back of a circular list
- compute list size and last-node access
- release one node or a full list
- print one stack in a readable format

This is one of the most reused helper layers in the project, because both the
algorithm and primitive move logic depend on the circular stack model.

## Dependency Role

This package sits underneath most of the rest of the codebase:

- parsing depends on node creation, insertion, and cleanup
- move operations depend on circular-list behavior and size helpers
- checker and startup code use the error-output helper
- debug and display code depend on stack-printing helpers

So while the helper package does not own any high-level project flow, it
supports nearly every runtime subsystem.

## Folder-Level Call Chains

The main function chains in this package are:

1. stack construction path -> `ft_new` -> `ft_add_back` or `ft_add_front`
2. stack cleanup path -> `ft_clear` -> `ft_delone`
3. stack display path -> `print_stack` -> `print_stack_values`
4. error-reporting path -> `ft_puterr_exit` -> `ft_puterr` -> `exit`

## Practical Role In The Project

The helper package is the shared support layer that keeps the rest of the
project smaller and more focused. Higher-level modules can rely on a stable set
of basic utilities instead of reimplementing node management, stack printing,
or simple error handling in multiple places.

That makes this package small in scope but broad in impact: it underpins the
runtime behavior of much of the codebase.