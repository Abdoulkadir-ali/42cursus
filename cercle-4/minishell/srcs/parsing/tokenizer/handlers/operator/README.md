# Operator Handlers

This directory implements tokenization of shell operators and punctuation
(`|`, `||`, `&`, `&&`, `<`, `<<`, `<<<`, `>`, `>>`, `;`, `(`, `)`, etc.). The
primary entry is `handle_separator()` which recognizes the concrete operator
form at the current scan cursor and returns a populated `t_token *`.

## Entry Path

`handle_separator(char **str)` in `operator.c` is the public entry.

The steps are:

1. Allocate a `t_token` and validate memory.
2. If the current character repeats (e.g. `|` or `&`), check for three or
   more repetitions (`check_three_repeated`) to detect invalid forms.
3. Try `handle_basic_ops()` to detect `|`, `||`, `&`, `&&`, and background
   `&`.
4. Try `handle_redirs()` to detect `<`, `<<`, `<<<`, `>`, `>>`, and the
   `>|` form.
5. Fall back to `try_handle_punctuation()` for `(`, `)`, and `;`.
6. On success return the token; on failure free resources and return `NULL`.

## Helpers

- `check_three_repeated()` prints a syntax error for sequences like `|||` or
  `&&&`.
- `set_token_and_advance()` builds the token `value` string and advances the
  scan cursor.

## Error behavior

- Invalid repetition, unknown operator forms, or allocation failures cause
  `handle_separator()` to return `NULL` and the tokenizer to stop with an
  error.
