# Environment Helpers Pipeline

This directory contains the functions that read, print, validate, and update
the shell environment used by builtin execution. The flow below is
function-oriented and follows the exact calls in this subtree.

## Sorted Printing Path

`print_sorted_env` in `print.c` prints the environment in export format.

The steps are:

1. Iterate through `envp`.
2. Duplicate each entry into a linked list.
3. Sort the list with `ft_lstsort` and `ft_strcmp`.
4. Print each sorted entry with `print_env_entry`.
5. `print_env_entry` writes `declare -x KEY="VALUE"` when the entry contains
   `=` and `declare -x KEY` otherwise.
6. Clear the temporary list.

This path is used by the export builtin when it runs with no operands.

## Direct Set Path

`ft_set_env` in `set.c` inserts or replaces one environment variable.

The steps are:

1. Reject a null key or missing environment array.
2. Build the new entry with `make_new_entry(key, value)`.
3. Resolve the existing slot with `get_env_index(key, state)`.
4. If the key already exists, call `replace_env_at`.
5. Otherwise call `append_env_entry`.
6. Keep `state->envp` synchronized with the updated array.

`make_new_entry` builds `KEY=` first, then appends the value when one exists.

`get_env_index` matches a key only when the next character is `=` or the end
of the string, so partial prefixes are rejected.

`replace_env_at` swaps one existing slot in place.
`append_env_entry` allocates a larger environment array and appends the new
entry at the end.

This path is used by execution helpers such as `cd` and external-command setup
when they must update shell variables directly.

## Identifier Validation Path

`is_valid_ident` in `utils.c` validates shell identifiers.

Its rules are:

- the identifier must not be null or empty
- the first character must be alphabetic or `_`
- later characters must be alphanumeric or `_`
- parsing stops before `=` when one is present

`count_env` in the same file returns the number of entries in a NULL-terminated
environment array.

## Export Parsing Path

`parse_export_arg` in `utils.c` decomposes one export operand into a reusable
context structure.

The steps are:

1. Locate `=` with `ft_strchr(arg, '=')`.
2. Detect append mode when the character before `=` is `+`.
3. Call `set_key_and_entry(arg, ctx)` when `=` is present.
4. `set_key_and_entry` extracts the key and duplicates the original operand.
5. If no `=` exists, duplicate the key and build `KEY=` as the provisional
   entry.

`report_invalid_identifier` prints the export identifier error and frees the
allocated context fields before returning `1`.

## Export Update Path

`process_export_arg` in `process/update.c` is the main export-update entry.

The steps are:

1. Zero-initialize `t_export_ctx`.
2. Parse the operand with `parse_export_arg(arg, &ctx)`.
3. Validate `ctx.key` with `is_valid_ident`.
4. If validation fails, return `report_invalid_identifier(arg, &ctx)`.
5. Resolve the current environment slot with `get_env_index(ctx.key, state)`.
6. If the key exists, call `process_existing_export(&ctx, &state->envp)`.
7. Otherwise call `process_new_export(&ctx, &state->envp)`.

## Existing Export Path

`process_existing_export` in `process/helpers.c` updates an existing variable.

The steps are:

1. Call `update_existing_env(*envp, ctx)`.
2. Free `ctx->key`.
3. Return `0`.

`update_existing_env` in `process/update.c` applies the exact update rule.

The rules are:

- when no `=` is present, keep the current variable unchanged
- when append mode is enabled, call `handle_append`
- otherwise call `handle_replace`

`handle_append` appends the new suffix to the existing entry.
If the existing variable has no `=`, it first rebuilds `KEY=` before appending
the new value.

`handle_replace` frees the old string and installs `ctx->new_entry` directly.

## New Export Path

`process_new_export` in `process/helpers.c` adds a brand-new variable.

The steps are:

1. If append mode is requested and `=` exists, build the real entry with
   `create_appended_entry(ctx)`.
2. `create_appended_entry` converts `KEY+=VALUE` into `KEY=VALUE`.
3. Append the resulting string with `push_new_env_entry(envp, ctx->new_entry)`.
4. Free `ctx->key`.
5. Return `0`.

`push_new_env_entry` allocates a larger environment array, copies the existing
entries, appends the new one, and frees the old array.

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `print_sorted_env` -> `print_env_entry`
2. `ft_set_env` -> `make_new_entry` -> `get_env_index` ->
   `replace_env_at` or `append_env_entry`
3. `process_export_arg` -> `parse_export_arg` -> `get_env_index` ->
   `process_existing_export` or `process_new_export`
4. `process_existing_export` -> `update_existing_env` ->
   `handle_append` or `handle_replace`
5. `process_new_export` -> `create_appended_entry` -> `push_new_env_entry`