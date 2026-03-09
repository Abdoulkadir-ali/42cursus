# Tokenizer Pipeline

This directory contains the functions that convert a raw command line into a
token stream and validate that stream against shell syntax rules before AST
building begins. The flow below is function-oriented and ties together the
`syntax` and `tokenizer` subdirectories with the shared helpers in `utils.c`.

## Global Pipeline

1. `tokenizer(str)` scans the raw input string and builds a linked list of
   `t_token` nodes.
2. The resulting list is then passed to `check_syntax(tokens)`.
3. The syntax layer validates parentheses, operators, semicolons, and
   redirection placement.
4. Shared helpers in `utils.c` provide redirection classification, syntax-error
   reporting, and token cleanup.

## Tokenization Path

`tokenizer` in `tokenizer/tokenizer.c` is the public entry point for lexical
analysis.

The steps are:

1. Skip spaces and shell comments with `skip_spaces_and_comments`.
2. Extract the next token with `get_next_token`.
3. Wrap the token into a list node with `add_token_to_list`.
4. Repeat until the input string is exhausted.

`get_next_token` routes tokenization by character class:

- separators and operators go to `handle_separator`
- everything else starts as a word through `handle_word`
- numeric words immediately followed by `<` or `>` are folded into fd-aware
  redirection tokens

## Syntax Path

`check_syntax` in `syntax/syntax.c` is the public entry point for syntax
validation.

The steps are:

1. Reject invalid first tokens through `check_initial_token`.
2. Walk the token list through `check_syntax_loop_and_last`.
3. For each node, call `process_node`.
4. `process_node` delegates to the rule helpers in `syntax/helper.c`.
5. After the loop, reject trailing `&&`, `||`, or `|` tokens.
6. Reject unmatched opening parentheses through `check_remaining_depth`.

The rule helpers are:

- `syntax_handle_lparen`
- `syntax_handle_rparen`
- `syntax_handle_pipe_and_logic`
- `syntax_handle_semicolon`
- `syntax_handle_redirection`

## Shared Helpers

`utils.c` provides the helpers shared by both halves of the subtree:

- `print_syntax_error` emits the standard shell syntax error and returns `2`
- `del_token` frees one token object for list cleanup
- `is_redirection` classifies redirection token types for both syntax and AST
  construction

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `tokenizer` -> `skip_spaces_and_comments` -> `get_next_token`
2. `get_next_token` -> `handle_separator` or `handle_word`
3. `check_syntax` -> `check_syntax_loop_and_last` -> `process_node`
4. `process_node` -> the rule helpers in `syntax/helper.c`