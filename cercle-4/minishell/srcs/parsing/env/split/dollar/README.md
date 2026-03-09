# Dollar Expansion Pipeline

This directory contains the functions that decide whether `$` expands or stays
literal, then route the result either into a plain string buffer or the token
splitting pipeline. The flow below is function-oriented and follows the exact
calls in this subtree.

## Entry Path

`handle_dollar_split` in `handler.c` is the public entry point for dollar
handling during split expansion.

The steps are:

1. Verify that the current character is `$`.
2. Build a `t_dollar_peek` with the current index and next character.
3. If `out->str` is active, call `expand_to_string`.
4. Otherwise call `expand_to_tokens`.
5. Return `1` when the dollar sequence was handled.

## String Output Path

`expand_to_string` is used when the caller is building one plain string rather
than a token list.

The rules are:

- inside single quotes, expansion is disabled
- otherwise expansion is allowed only when `is_exp_target(peek->next)` is true
- if expansion is not allowed, keep the dollar literal through
  `push_literal_dollar`
- if expansion is allowed, call `perform_expansion`

This path is used by generic string expansion helpers that do not want
word-splitting behavior.

## Token Output Path

`expand_to_tokens` is used when the caller is building token output.

The steps are:

1. Call `is_unquoted_quote(peek, st)`.
2. If the next character is an unquoted quote, skip the dollar and return.
3. Otherwise call `is_bad_target(peek, st)`.
4. `is_bad_target` rejects expansion when the next character is not a valid
   target, when the parser is inside single quotes, or when `$"` appears inside
   double quotes.
5. If the target is bad, keep the dollar literal through `push_literal_dollar`.
6. Otherwise call `perform_expansion`.

## Decision Helpers

`is_unquoted_quote` detects `$'` and `$"` when the parser is currently outside
both quote modes.

`is_bad_target` implements the remaining literal-dollar cases:

- invalid target character after `$`
- any dollar inside single quotes
- `$"` while already inside double quotes

## Expansion Handoff

Both `expand_to_string` and `expand_to_tokens` delegate real value resolution
to `perform_expansion`, which then calls `handle_dollar` in the parent split
directory.

From there, the pipeline continues through:

1. `handle_special_dollar` for `$?`, `$$`, and bare trailing `$`
2. `handle_var_name` for normal variable names
3. `get_env_value` for final environment lookup

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `handle_dollar_split` -> `expand_to_string`
2. `handle_dollar_split` -> `expand_to_tokens`
3. `expand_to_string` or `expand_to_tokens` -> `perform_expansion`
4. `perform_expansion` -> `handle_dollar`
