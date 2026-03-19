# Env Split Pipeline

This directory contains the functions that expand one shell word, track quote
context, split unquoted expansion results into tokens, and preserve escape data
needed by later wildcard processing. The flow below is function-oriented and
follows the exact calls in this subtree.

## Entry Path

`expand_and_split` in `split.c` is the public entry point.

The steps are:

1. Initialize a `t_expansion` context with the source string, environment, and
   last exit status.
2. Call `run_expansion_loop(&exp)`.
3. Pass the resulting buffers to `finalize_expansion(&exp.output, &exp.state)`.
4. Return the token list produced by expansion.

## Main Expansion Loop

`run_expansion_loop` scans the source string one character at a time.

At each position it tries handlers in this exact order:

1. `handle_quote_split`
2. `handle_backslash_split`
3. `handle_dollar_split`

If none of those handlers consume the character:

- quoted `*` and `?` are protected by pushing the internal `\001` marker first
- the current character is appended literally through `exp_push_char`
- quote-state bookkeeping is updated before advancing the cursor

## Finalization Path

`finalize_expansion` converts the accumulated buffers into the final token list.

The rules are:

- when `out->word` is non-empty, emit one token with `add_token_node`
- when no word remains but quote handling marked the result as quoted, emit an
  empty quoted token
- otherwise return the accumulated head as-is

## Quote Path

`handle_quote_split` in `quote.c` manages single and double quote state.

Its routing is exact:

1. On `'`, call `toggle_single_quote`.
2. On `"`, call `toggle_double_quote`.
3. Otherwise return `0`.

`toggle_single_quote` only works outside double quotes.
`toggle_double_quote` only works outside single quotes.
Both helpers call `mark_as_quoted`, which records that quotes influenced the
current token and ensures an empty quoted token can still be emitted later.

## Backslash Path

`handle_backslash_split` in `backslash.c` processes backslashes unless the
parser is currently inside single quotes.

The steps are:

1. If inside double quotes, first try `handle_dq_backslash`.
2. `handle_dq_backslash` only treats `$`, `"`, `\\`, and newline as special.
3. For every handled backslash path, `consume_backslash` moves past the
   backslash, appends the escaped character, and preserves quoted wildcard data
   with the internal `\001` marker when needed.

## Dollar Path

`handle_dollar_split` in `dollar/handler.c` dispatches dollar handling.

Its routing is exact:

1. If the current character is not `$`, return `0`.
2. Build a `t_dollar_peek` containing the current index and next character.
3. If `out->str` is active, call `expand_to_string`.
4. Otherwise call `expand_to_tokens`.

See `dollar/README.md` for the detailed dollar-expansion subpipeline.

## Value Resolution Path

`handle_dollar` in `env.c` resolves the value for one dollar-prefixed target.

The steps are:

1. Call `handle_special_dollar`.
2. `handle_special_dollar` handles the cases `$`, `$?`, and `$$`.
3. If no special form matches, call `handle_var_name`.
4. `handle_var_name` parses either one digit or a standard shell variable name.
5. It then resolves the final string through `get_env_value`.

`get_env_value` has one special case for `UID`, then falls back to `ft_get_env`
and returns an empty allocated string when the variable is undefined.

## Split-On-Whitespace Path

When unquoted dollar expansion produces a string in token mode,
`perform_expansion` may delegate to `process_val_split` in `process.c`.

The steps are:

1. Iterate across the expanded value.
2. On whitespace, call `flush_token` to close the current token.
3. On non-whitespace, append characters through `exp_push_char`.

This is what turns unquoted expanded values into multiple shell words.

## Shared Output Helpers

The shared helpers in `exp.c` and `utils.c` support all paths:

- `is_exp_target` validates the character after `$`
- `exp_push_char` and `exp_push_str` append data to either string or token mode
- `perform_expansion` runs `handle_dollar` and chooses between direct append
  and word splitting
- `push_literal_dollar` keeps `$` unchanged when expansion is not allowed
- `apply_tilde_expansion` expands leading `~` when quoting allows it
- `append_chunk` concatenates allocated string pieces

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `expand_and_split` -> `run_expansion_loop` -> `finalize_expansion`
2. `run_expansion_loop` -> `handle_quote_split` or
   `handle_backslash_split` or `handle_dollar_split`
3. `handle_dollar_split` -> `expand_to_string` or `expand_to_tokens`
4. `expand_to_string` or `expand_to_tokens` -> `perform_expansion` ->
   `handle_dollar`
5. `perform_expansion` -> `process_val_split` when token-mode splitting is
   required
