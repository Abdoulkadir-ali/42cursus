# Word Handlers

This directory implements tokenization of shell words: unquoted runs and
quoted fragments that compose a single logical word. It also detects
assignment prefixes (e.g. `VAR=value`).

Primary entry: `handle_word(char **str)` which returns a filled `t_token *`.

## Entry Path

`handle_word` is called when the tokenizer finds a non-operator, non-space
character. The high-level steps are:

1. Call `collect_word()` to build the complete word string.
2. `collect_word()` uses `collect_word_loop()` which repeatedly extracts
   chunks (`get_chunk`) until a separator or space is found.
3. `get_chunk()` returns quoted fragments (via `scan_quoted`) or unquoted
   runs (via `scan_unquoted`). Quoted fragments preserve literal content and
   set the `quoted` flag.
4. After collecting, `handle_word()` classifies the token as
   `TOKEN_PREFIX` when it matches the assignment prefix pattern
   (`is_assignment_prefix()`), otherwise `TOKEN_WORD`.
5. The token's `quoted` and `expanded` flags are set accordingly and the
   token is returned.

## Quote and escape handling

- `scan_quoted()` recognizes quoted fragments and supports backslash
  escapes inside double quotes.
- `scan_unquoted()` counts characters in an unquoted run, treating backslash
  as an escape for the next character.

## Error handling

- If a quoted fragment is not closed, `get_chunk()` reports a syntax error
  and returns `NULL` causing tokenization to abort.
- Memory allocation failures return `NULL`.
