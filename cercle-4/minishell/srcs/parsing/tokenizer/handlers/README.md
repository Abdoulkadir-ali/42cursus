# Tokenizer Handlers

This directory contains the small handler functions used by the tokenizer to
classify and build individual tokens from the input string. Handlers are
function-oriented and designed to be invoked by the main tokenizer loop.

The subtree is split into operator and word handlers. Each handler returns a
fully initialized `t_token *` on success or `NULL` on failure.

## Entry Path

The tokenizer (`tokenizer.c`) calls handlers when it detects the start of an
operator or a word. The typical flow is:

1. Inspect the next character in the input.
2. If it is whitespace, skip it.
3. If it matches an operator starting set (`|&<>();`), call the operator
   handler (`operator/handle_separator`).
4. Otherwise call the word handler (`word/handle_word`).
5. The returned `t_token` is appended to the token list by the tokenizer.

## Error handling

- Handlers return `NULL` on allocation failure or when a syntax error is
  detected (e.g., unclosed quotes, invalid operator repetition).
- When handlers detect syntax errors they print a message and return `NULL`.

See the `operator/` and `word/` subdirectories for implementation details.
