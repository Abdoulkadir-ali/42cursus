# Display Helper Module

This directory currently contains the error-output helper used across the
project. In the current `push_swap` flow, this package is the smallest part of
the helper layer: it does not own stack printing anymore, and instead focuses
only on reporting failures through a shared interface.

The implementation here is very small, but it still performs two distinct jobs:

- print an error message to standard error
- optionally terminate the process immediately after printing the error

## Error Output Path

`ft_puterr` in `ft_puterr.c` is the basic error-reporting helper.

The steps are:

1. Print the provided message to file descriptor `2`.
2. Return `1`.

This return value makes the helper convenient in compact error paths where the
caller wants to both report failure and immediately return a non-zero status.

## Exit-On-Error Path

`ft_puterr_exit` in `ft_puterr.c` builds on the previous helper.

The steps are:

1. Print the error message with `ft_puterr`.
2. Terminate the process with `exit(1)`.

This gives the project a direct failure path for cases where continuing runtime
execution would not make sense.

## Layout Note

This folder used to be responsible for more display-oriented helpers, but the
current layout is different:

- stack-printing helpers now live in `../lst/`
- this folder now contains only the error-output helper layer

That means the name `display` is broader than the current implementation, but
the contents are still useful as a shared output utility module.

## Folder-Level Call Chains

The main function chain in this subtree is:

1. `ft_puterr_exit` -> `ft_puterr` -> `exit`

## Practical Role In The Project

This module is small, but it gives parsing and startup code a consistent way to
report runtime failures without duplicating file-descriptor handling or return-
value conventions.

That keeps failure paths short and uniform across the codebase.