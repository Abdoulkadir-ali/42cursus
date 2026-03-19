# Tokenizer Syntax Pass

This subtree validates token sequences produced by the tokenizer to ensure
they form a syntactically valid shell command stream. The style below is
function-oriented and mirrors other reader docs so the call flow is easy to
follow.

## Entry Path

`check_syntax(t_nodes *tokens)` in `syntax.c` is the public entry used after
tokenization and expansion.

The steps are:

1. Call `check_initial_token(tokens)` to reject tokens that may not start a
   command (`|`, `;`, `&&`, `||`, `&`).
2. Iterate over each token node and call `process_node(curr, &depth)`.
3. After the pass, verify `depth == 0` to ensure parentheses are balanced.
4. Return `0` on success or `2` on syntax error.

## Per-node processing

`process_node()` delegates to `process_rules()` which dispatches by token
type.

Rules covered:

- Parentheses (`(` and `)`) — `syntax_handle_lparen` increments depth and
  rejects invalid followers; `syntax_handle_rparen` decrements depth and
  rejects unexpected followers and reports unbalanced `)` when depth < 0.
- Pipes and logical operators (`|`, `||`, `&&`) — `syntax_handle_pipe_and_logic`
  rejects invalid next tokens (another operator, `)`, `;`, `&`).
- Semicolon and background (`;`, `&`) — `syntax_handle_semicolon` ensures
  the following token is not an operator that would be syntactically wrong.
- Redirections (`<`, `>`, `<<`, `>>`, `<<<`, `>|`) — `syntax_handle_redirection`
  requires a following word or prefix token unless the redirection token is
  marked `expanded` (i.e., came from expansion) in which case the caller
  expects the expansion pass to have produced a valid target.

On any rule violation the helper prints a syntax error and `check_syntax`
returns `2`.

## Error behavior

- `print_syntax_error()` is used to emit the offending token label and
  returns a non-zero code that the caller propagates.
- The syntax pass sets no global state itself but helps callers map parse
  failures to `state->syntax_error` where needed.

## Folder-level call chains

1. `check_syntax` -> `check_initial_token`
2. `check_syntax` -> `process_node` -> `process_rules` -> (specific rule)

For exact signatures and detailed behavior, see the source files in this
directory: `syntax.c`, `process.c`, and `cases.c`.
