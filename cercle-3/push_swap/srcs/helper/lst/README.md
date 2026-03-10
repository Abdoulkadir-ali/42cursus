# List Helper Module

This directory contains the custom linked-list helpers used by the project to
manage stack nodes. In the current `push_swap` flow, this package is the low-
level container layer for stack storage: it creates nodes, links them into the
project's circular list representation, and provides the basic traversal and
cleanup helpers used by parsing, moves, and algorithm code.

The implementation here is small, but it does several distinct jobs:

- allocate and initialize a new stack node
- add a node to the back of a circular list
- add a node to the front of a circular list
- find the last node of a circular list
- count the number of nodes in the list
- print one stack in a readable form
- free one node or clear the full list

## Data Structure Role

The most important detail of this package is that the stack lists are treated
as circular linked lists.

That means:

- the last node points back to the head
- traversal helpers must detect when they return to the start
- insertion helpers must preserve the circular structure

This design affects every function in the folder and explains why the helpers
look different from a standard null-terminated singly linked list API.

## Node Creation Path

`ft_new` in `ft_new.c` allocates and initializes one `t_nodes` element.

The steps are:

1. Allocate memory for a new node.
2. Return `NULL` if allocation fails.
3. Store the integer value in `v`.
4. Reset all metadata fields to neutral defaults.
5. Initialize `next` to `NULL`.
6. Return the new node.

This function gives the rest of the project a clean starting point for node
construction before the node is linked into a stack.

## Size Computation Path

`ft_size` in `ft_size.c` counts the number of nodes in a circular list.

The steps are:

1. Return `0` if the list is empty.
2. Store the starting node.
3. Walk forward node by node.
4. Increment the counter at each step.
5. Stop when traversal returns to the start node.

This helper is used throughout the project because many algorithm decisions are
based on current stack length.

## Stack Print Path

`print_stack` in `ft_print_lst.c` is the public entry point for displaying one
stack.

The steps are:

1. Print the provided stack name.
2. Print the separator ` : `.
3. Print `(empty)` if the stack does not exist.
4. Otherwise delegate the value traversal to `print_stack_values`.
5. End the line with a newline.

This function gives the rest of the project a simple way to inspect stack
content without duplicating formatting logic.

## Value Traversal Path

`print_stack_values` in `ft_print_lst.c` performs the actual iteration over the
nodes.

The steps are:

1. Return immediately if the stack is null.
2. Compute the stack size.
3. Walk through every node.
4. Print each integer value followed by `, `.
5. Remove the trailing separator with backspace characters.

The result is a compact comma-separated representation of the current stack
content.

## Last Node Path

`ft_last` in `ft_last.c` returns the last node of the circular list.

The steps are:

1. Return `NULL` if the list is empty.
2. Compute the list size.
3. Walk forward until only one step remains.
4. Return the current node.

In this structure, the last node is the one whose `next` pointer leads back to
the head of the stack.

## Add-To-Back Path

`ft_add_back` in `ft_add_back.c` appends a node to the end of the circular
list.

The full flow is:

1. Return immediately if the new node is null.
2. If the list is empty, make the node point to itself and store it as the head.
3. Otherwise find the last node with `ft_last`.
4. Link the old last node to the new node.
5. Link the new node back to the head.

This preserves the circular shape while leaving the head pointer unchanged.

## Add-To-Front Path

`ft_add_front` in `ft_add_front.c` inserts a node at the head of the circular
list.

The steps are:

1. Return immediately if the new node is null.
2. If the list is empty, make the node point to itself and store it as the head.
3. Otherwise find the last node with `ft_last`.
4. Link the new node to the current head.
5. Link the old last node to the new node.
6. Replace the head pointer with the new node.

This version updates both the tail connection and the visible start of the
stack.

## Single-Node Free Path

`ft_delone` in `ft_delone.c` frees one node.

Its role is simple:

- return immediately for a null pointer
- otherwise free the node memory

This helper does not relink neighboring nodes. It assumes the caller already
controls the list structure.

## Full Clear Path

`ft_clear` in `ft_clear.c` releases every node in a stack.

The full flow is:

1. Return immediately if the list pointer or list is null.
2. Compute the list size.
3. Repeatedly store the current head.
4. Advance the head pointer to the next node.
5. Free the saved node with `ft_delone`.
6. Continue until all nodes are released.
7. Set the final list pointer to `NULL`.

This function is safe for the circular list layout because it uses the original
size instead of relying on a null terminator.

## Dependency Role

This folder provides the basic container operations needed by the rest of the
project:

- parsing code uses it to build stacks from input
- move code depends on the circular structure during rotations
- algorithm code relies on `ft_size` and list traversal behavior
- debug and inspection code use `print_stack`
- cleanup code uses `ft_clear` and `ft_delone`

So while these helpers are simple, they support almost every major subsystem.

## Folder-Level Call Chains

The main function chains in this subtree are:

1. Node creation path -> `ft_new`
2. Back insertion path -> `ft_add_back` -> `ft_last` -> `ft_size`
3. Front insertion path -> `ft_add_front` -> `ft_last` -> `ft_size`
4. Stack display path -> `print_stack` -> `print_stack_values` -> `ft_size`
5. Clear path -> `ft_clear` -> `ft_size` -> `ft_delone`

## Practical Role In The Project

The list helper module gives the project a custom stack container tailored to
its rotation-heavy behavior. Because the stacks are circular, many operations
can move the head pointer or reconnect nodes without constantly traversing to a
null end.

That makes this package small but foundational: it defines the storage model on
top of which parsing, movement, and algorithm decisions all operate.