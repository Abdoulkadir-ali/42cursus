# Wildcard Match Pipeline

This directory contains the functions that compare one wildcard pattern against
directory entries and build the raw result list used by wildcard expansion.

## Collection Flow

`collect_matches` in `match.c` is the submodule entry point.

Its call chain is:

1. `prepare_pattern(pattern, &require_dir)` duplicates the pattern and strips
   trailing `/` characters.
2. `process_directory(dir, pat_copy, require_dir)` scans directory entries.
3. `process_directory` calls `check_entry` for each `readdir` result.
4. `check_entry` calls `should_skip_entry` and `match_pattern`.
5. Accepted entries are appended by `try_add_match`.

## Directory Scan Rules

`process_directory` applies two safety caps while scanning:

1. it stops reading after `10000` entries
2. it stores at most `100` matches through `try_add_match`

Those limits keep expansion bounded even in very large directories.

## Entry Filtering

`should_skip_entry` rejects entries that should not participate in the match:

1. hidden entries when the pattern does not start with `.`
2. the literal `.` and `..` entries
3. an entry that is exactly equal to the raw pattern text

`prepare_pattern` also detects trailing `/` characters and raises
`require_dir`, which later forces accepted matches to be directories.

`check_entry` enforces that directory-only mode by using `d_type` when
available and falling back to `stat` for `DT_UNKNOWN` entries.

## Pattern Matching

`match_pattern` is the public matcher for one pattern-entry pair.

Its steps are:

1. Initialize the backtracking state used for `*` handling.
2. Run the main character-by-character matcher through `match_loop`.
3. Consume any trailing `*` characters left in the pattern.
4. Accept the match only when the pattern is fully consumed.

`match_loop` in `loop.c` implements the actual wildcard engine.

It recognizes:

1. `*` as a backtracking wildcard through `set_star` and `backtrack_to_star`
2. `?` as a single-character wildcard
3. escaped wildcard bytes marked with `\001`, which must match literally
4. direct character equality

`advance_both` moves pattern and string together after a successful
single-character match.

`is_wildcard` is the companion detector used by callers before expansion. It
ignores escaped wildcard bytes so only active metacharacters trigger the module.