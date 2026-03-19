# Command AST helpers (ast/cmd)

This subtree converts a token segment representing a single simple command
(one pipeline element) into a finalized `t_ast` command node. It scans the
token stream, counts and collects assignment prefixes and argument words,
builds the `argv` array, and attaches redirections.

The structure and wording below follow the function-oriented, step-by-step
style used in the reader subsystem documentation so callers can trace the
exact call chains.

## Entry Path

`handle_simple_cmd` in `finalize.c` is the high-level entry used by the AST
builder for simple command segments.

The steps are:

1. Call `scan_command_tokens(tokens, &cmd, &is_quoted)` to populate `cmd`
   meta (`count`, `prefix_count`) and detect whether the first word is
   quoted.
2. If `cmd.prefix_count > 0`, call `collect_prefixes(tokens, cmd.prefix_count)`
   to duplicate leading assignment prefixes into a new array.
3. If `cmd.count == 0`, call `process_redirections(NULL, tokens)` to build a
   redirection-only node and return it.
4. Call `build_args_from_tokens(tokens, cmd.count)` to allocate and fill the
   `argv` array.
5. Create the `t_ast` node with the resulting `args` and optional `assigns`.
6. Call `process_redirections(node, tokens)` to attach redirection nodes.
7. Set `node->is_quoted` when appropriate and return the finalized node.

If any allocation fails, the function frees partially-built state and
returns `NULL`.

## Scanning Path

`scan_command_tokens` in `scanner.c` walks the token list until a pipe or
end, counting words and prefixes.

The steps are:

1. Initialize `cmd->count = 0`, `cmd->prefix_count = 0`, `seen_word = 0`.
2. For each token until `TOKEN_PIPE`:
   - If token is `TOKEN_WORD`, mark `seen_word = 1`, record `is_quoted` for
     the first word, and increment `cmd->count`.
   - Else if token is `TOKEN_PREFIX`, increment `cmd->prefix_count` when
     `seen_word == 0`, otherwise increment `cmd->count` (prefix after a
     word becomes an argument).
   - Else if token is a redirection operator and `curr->next` exists,
     skip the next node (filename) so it is not counted.
3. Return with `cmd` filled.

## Collection Path

The collection helpers in `collect.c` duplicate tokens into heap-allocated
string arrays.

`collect_prefixes(tokens, count)` steps:

1. Allocate a `char **` array of size `count + 1`.
2. Walk tokens, copying up to `count` `TOKEN_PREFIX` values with `ft_strdup`.
3. Skip redirection targets when a redirection operator is encountered.
4. NULL-terminate and return the array.

`build_args_from_tokens(tokens, count)` steps:

1. Allocate a `char **` array sized for `count + 1`.
2. Walk tokens until `TOKEN_PIPE`, copying `TOKEN_WORD` and post-word
   `TOKEN_PREFIX` values into the array.
3. Skip redirection targets (next token after a redirection operator).
4. NULL-terminate and return the array.

## Finalization and Redirections

`handle_simple_cmd` calls `process_redirections()` to transform any remaining
redirection operator / filename pairs into attached redirection nodes on the
returned `t_ast` node. If the command contained only redirections and no
words, the returned AST node represents those redirections (no `args`).

Redirection processing rules (summary):

- Operators consume the next token as their filename/target; the collector
  intentionally skips those so filenames are handled by `process_redirections`.
- When wildcard/expansion has already been applied, quoted status is
  propagated to the `t_ast` node via `is_quoted`.

## Memory and errors

- All arrays and nodes returned are heap-allocated; callers or AST cleanup
  helpers must free them.
- On allocation failure, helpers free partial state and return `NULL`.

## Folder-level call chains

Main chains used by the AST builder:

1. `handle_simple_cmd` -> `scan_command_tokens` -> `collect_prefixes`
2. `handle_simple_cmd` -> `scan_command_tokens` -> `build_args_from_tokens`
3. `handle_simple_cmd` -> `process_redirections`

For exact signatures and detailed error paths, see `scanner.c`,
`collect.c`, and `finalize.c` in this directory.
