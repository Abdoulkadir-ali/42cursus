# Expansion & Split Submodule

This subtree implements quote-aware word expansion and field splitting used
by the parser. It turns one raw word string into a linked list of `t_token`
nodes according to shell expansion rules: tilde expansion, parameter
expansion (`$`), quote handling, backslash escapes, field splitting on
unquoted whitespace, and preservation of quoted/null results.

The documentation below follows the function-oriented, step-by-step style
used across the repository so callers can follow exact call chains.

## Entry Path

`expand_and_split(char *str, char **env, int status)` in `split.c` is the
public entry point. It returns a `t_nodes *` list of tokens produced from the
input string.

The steps are:

1. Initialize a `t_expansion` context with the input string, `env`, and
   `status`.
2. Run `run_expansion_loop(&exp)` to process characters one-by-one.
3. Finalize the expansion with `finalize_expansion(&exp)`, which flushes any
   pending word and returns the token-list head.

On `NULL` input, the function returns `NULL`.

## Expansion loop

`run_expansion_loop()` is the per-character driver that evaluates the input
string under the current quote/split state.

The loop steps are:

1. If `handle_quote_split(exp)` returns true, continue (toggles single/double
   quote states and records `has_quotes`).
2. If `handle_backslash_split(exp)` returns true, continue (consumes
   backslash escapes, with double-quote specific rules).
3. If `handle_dollar_split(exp)` returns true, continue (performs `$`-
   driven expansions including `$?`, `$$`, and variable names).
4. When inside quotes and a glob character is seen (`*` or `?`), the code
   pushes an internal escape marker (`\001`) to protect it from later
   globbing.
5. Append the current character to the active output buffer with
   `exp_push_char()` and advance the cursor.

After the loop, `finalize_expansion()` converts the built buffers into token
nodes: if `exp.word` exists it is appended as a `TOKEN_WORD` (with the
`has_quotes` flag), otherwise when quotes were present an empty quoted token
is produced.

## Dollar / variable handling

`handle_dollar_split()` orchestrates dollar expansions. Key rules:

- `$?` → expanded to the provided `status` number.
- `$$` → expanded to the current PID.
- Numeric or alphanumeric names → resolved via `get_env_value()` which
  returns `ft_get_env()` values or an empty string when undefined.
- When expansion occurs in unquoted mode, the replacement is subject to
  field splitting via `process_val_split()`; when inside double quotes the
  result is appended as a single chunk and marks `has_quotes`.

`perform_expansion()` (in `exp.c`) drives this flow and integrates result
handling between `exp->res_str` (accumulating a replacement string) and
`exp->word` (current token under construction).

## Backslash and quote behavior

- `handle_quote_split()` toggles `in_s_quote` / `in_d_quote` and ensures
  `has_quotes` is recorded; empty quoted words produce an empty token.
- `handle_backslash_split()` consumes escapes. Outside quotes it treats a
  backslash as escaping the next character (and marks `has_quotes`). Inside
  double quotes only `\`, `"`, `$`, and newline are special; other backslashes
  are preserved literally.

## Field splitting

`process_val_split()` splits expanded values on unquoted whitespace. Its
behavior:

1. For each character in the expanded value, if it's whitespace, flush the
   current `exp->word` into the token list via `flush_token()`.
2. Otherwise append the character to the active buffer.

This ensures unquoted expansions that contain spaces produce multiple tokens
while quoted expansions remain a single token.

## Ancillary helpers

- `apply_tilde_expansion()` replaces leading `~` with the `HOME` value when
  the token is not quoted.
- `strip_glob_escapes()` removes internal escape markers (`\001`) left by
  backslash handling that were used to protect `*`/`?` during splitting.
- `create_token_node_from_match()` (used by globbing) converts filesystem
  match strings into token nodes.
- `append_chunk()` merges temporary chunk strings into the active result.

## Memory and errors

- The module constructs token nodes via `add_token_node()` and returns a
  list owned by the caller.
- Empty-but-quoted results produce an explicit empty token node (not NULL).
- Functions free partial buffers on error; callers must free returned token
  lists when appropriate.

## Folder-level call chains

1. `expand_and_split` -> `run_expansion_loop` -> `handle_quote_split`
2. `run_expansion_loop` -> `handle_backslash_split` -> `consume_backslash`
3. `run_expansion_loop` -> `handle_dollar_split` -> `perform_expansion` ->
   `process_val_split`

For exact signatures and edge cases, see the source files in this
directory: `split.c`, `exp.c`, `dollar.c`, `backslash.c`, `quote.c`, and
`utils.c`.
