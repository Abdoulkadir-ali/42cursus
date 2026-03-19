# Tokenizer Pipeline

This subtree converts a raw command line into a validated token stream
ready for AST construction. The README is function-oriented so you can map
each step to the actual implementation in `tokenizer.c`, `handlers/`, and
`syntax/`.

## Global Pipeline

1. `tokenizer(str)` produces a linked list of `t_token` nodes.
2. The token list is passed to `check_syntax(tokens)` for validation.
3. On success the validated token list is returned to the parser/builder.

Shared helpers in this subtree (`utils.c`) provide common utilities such as
`print_syntax_error`, `del_token`, and `is_redirection`.

---

## Tokenization Path

`tokenizer(char *str)` in `tokenizer.c` is the public entry for lexical
analysis.

The steps are:

1. Call `skip_spaces_and_comments(&str)` to consume whitespace and `#` comments.
2. Call `get_next_token(&str)` to obtain the next `t_token *`.
3. Wrap the token into a list node and append it to the accumulator.
4. Repeat until the input is exhausted or an error occurs.

`get_next_token` routing rules:

- If the current character is an operator/punctuation (`|<>()&;`), call
   `handle_separator(&str)` (operator handlers live in `handlers/operator`).
- Otherwise call `handle_word(&str)` (word handlers live in `handlers/word`).
- After building a word token, `handle_numeric_redirections` merges a
   leading numeric token with a following redirection operator (e.g. `2>` →
   `TOKEN_RED_OUT` with value `2>`).

Error behavior:

- If a handler returns `NULL` (syntax error, unclosed quote, allocation
   failure), `tokenizer()` frees accumulated tokens and returns `NULL`.

---

## Syntax Validation Path

`check_syntax(t_nodes *tokens)` in `syntax/syntax.c` validates the token
sequence.

The steps are:

1. Reject forbidden initial tokens via `check_initial_token` (operators that
    may not start a command).
2. Iterate tokens and call `process_node(curr, &depth)` for each node.
3. Each node delegates to `process_rules()` which routes to specific rule
    helpers (`cases.c`) depending on token type.
4. After iteration ensure `depth == 0` to confirm balanced parentheses.
5. Return `0` on success or `2` on syntax error.

Rule highlights:

- Parentheses (`(` / `)`) adjust depth and reject invalid followers.
- Pipes and logical operators reject invalid next tokens (another operator,
   `)`, `;`, `&`).
- Semicolon and background operators check that the following token is not
   another operator.
- Redirections require a following `TOKEN_WORD` or `TOKEN_PREFIX` unless the
   redirection token was produced by expansion and marked `expanded`.

On error helpers call `print_syntax_error()` which prints a message and the
syntax pass returns `2`.

---

## Handlers and helpers

- `handlers/operator` recognizes `|`, `||`, `&`, `&&`, `<`, `<<`, `<<<`, `>`,
   `>>`, `>|`, `(`, `)`, and `;` forms and returns a `t_token *` or `NULL`.
- `handlers/word` builds word tokens by concatenating quoted and
   unquoted chunks, detects assignment prefixes, and returns `TOKEN_WORD` or
   `TOKEN_PREFIX` tokens.
- Utility helpers in `handlers/*/helper.c` provide small routines such as
   `is_assignment_prefix`, `scan_quoted`, `scan_unquoted`, and `set_token_and_advance`.

---

## Folder-Level Call Chains

1. `tokenizer` -> `skip_spaces_and_comments` -> `get_next_token`
2. `get_next_token` -> `handle_separator` or `handle_word` -> `handlers/*`
3. `tokenizer` -> append token nodes -> return token list
4. `check_syntax` -> `process_node` -> `process_rules` -> `cases.c` helpers

For implementation details, see `tokenizer.c`, the `handlers/` subfolders,
and the `syntax/` subfolder.