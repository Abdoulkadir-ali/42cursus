# parsing/utils

Purpose
- Collection of small helpers used across the parsing subsystem: token checks,
  token-list to array conversions, safe string-array freeing, syntax error
  reporting, token deallocation and redirection-type checks.

Overview
- `token.c` provides predicate helpers and utilities that operate on the token
  structures used by the tokenizer and AST builders:
  - `cmp_node_type()` — compare a `t_nodes` list node's token type.
  - `cmp_tok_type()` — compare a `t_token` object's type.
  - `cmp_ast_type()` — compare an AST node's type.
  - `token_list_to_array()` — duplicate a linked list of token values into a
    NULL-terminated `char **` array (caller must free with `free_string_array`).
  - `free_string_array()` — safely free a NULL-terminated `char **`.

- `utils.c` exposes small parsing helpers used by the tokenizer, syntax check
  code and list cleanup routines:
  - `print_syntax_error()` — print a shell-style syntax error and return `2`.
  - `del_token()` — free a `t_token` object and its owned value string.
  - `is_redirection()` — predicate for the shell redirection token types.

Usage & responsibilities
- These helpers are intentionally small and low-level:
  - Tests and higher-level parsing code should not duplicate their behavior;
    call them instead of reimplementing checks or freeing logic.
  - `token_list_to_array()` is commonly used when building argument arrays
    for AST nodes or when preparing tokens for expansion routines.
  - `del_token()` is intended for use with generic list cleanup functions that
    accept a `void (*del)(void *)` callback.

Examples
- Convert tokens -> argv-style array:

  - Call `token_list_to_array(token_list)` to get a `char **` where each entry
    is a duplicate of the token `value` field. Remember to call
    `free_string_array()` when finished.

- Check a node type quickly:

  - Use `cmp_node_type(node, TOKEN_WORD)` to test whether a node contains a
    `TOKEN_WORD` token.

Notes
- These helpers assume ownership semantics used across the parsing code:
  token `value` strings are heap-allocated and must be freed by callers that
  destroy token objects.

See also
- `srcs/parsing/tokenizer` — lexical analysis and token creation.
- `srcs/parsing/ast` — AST construction and token consumption patterns.
