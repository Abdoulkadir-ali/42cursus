# parsing/wildcard

Purpose
- Wildcard (glob) expansion utilities used by the parsing pipeline to expand
  token text containing `*` or `?` into ordered filename lists.

Overview
- The wildcard package composes three responsibilities spread across files:
  - `expand.c` — public entry point `expand_wildcard()` that opens the
    current directory, collects matches and returns a sorted list of filenames.
  - `match/` — low-level match engine (see `match/README.md`) that performs
    pattern normalization, `*`/`?` matching, dotfile rules and directory-only
    matches for trailing-slash patterns.
  - `sort.c` — in-place lexical ordering of collected matches (`sort_list()`).

Behavior details
- `expand_wildcard(char *pattern)` returns `NULL` when the input contains no
  active metacharacters or when no matches are found. When matches exist the
  function returns a `t_nodes *` linked list with `char *` filenames in
  lexicographical order. The caller owns the returned list and must free the
  node objects and strings.

- Sorting uses a simple bubble-sort over the `t_nodes` list by swapping the
  `content` pointers — stable and acceptable for the small result sets the
  code expects.

Usage
- Typical expansion flow within the parser/expander:
  1. Detect active wildcard with `is_wildcard()`.
  2. Call `expand_wildcard(pattern)` to obtain matches.
  3. For each returned filename, create tokens or append to the argument list.
  4. Free the returned `t_nodes *` and contained strings when done.

See also
- `srcs/parsing/wildcard/match/README.md` — implementation details for
  pattern matching and collection.
# Wildcard Expansion Pipeline

This directory contains the functions that detect wildcard patterns, enumerate
the current directory, filter entries through shell-style matching rules, and
sort the final expansion list before the parser reinjects the results.

## Global Flow

The wildcard pipeline starts when a token is checked for active metacharacters.

1. `is_wildcard(str)` decides whether a token still contains active `*` or `?`
   characters.
2. `expand_wildcard(pattern)` opens the current directory and starts the
   expansion.
3. `expand_wildcard` calls `collect_matches(dir, pattern)`.
4. `collect_matches` normalizes the pattern through `prepare_pattern` and then
   scans the directory through `process_directory`.
5. `process_directory` evaluates each entry through `check_entry` and stores
   matches through `try_add_match`.
6. The final list is sorted by `sort_list` before it is returned.

## Entry Point

`expand_wildcard` in `expand.c` is the public expansion entry.

Its behavior is exact:

1. Return immediately when the pattern contains neither `*` nor `?`.
2. Open `.` with `opendir`.
3. Collect matches with `collect_matches`.
4. Close the directory stream.
5. Sort the match list with `sort_list`.
6. Return the sorted list.

## Sorting Stage

`sort_list` in `sort.c` reorders the linked list in place with `strcoll`, so
the final expansion follows locale-aware lexical ordering.

`swap_contents` performs the payload exchange between two list nodes during that
sort.

## Match Submodule

The `match` subdirectory owns directory scanning and wildcard comparison.

Its main call chain is:

1. `collect_matches` -> `prepare_pattern`
2. `collect_matches` -> `process_directory`
3. `process_directory` -> `check_entry`
4. `check_entry` -> `should_skip_entry`
5. `check_entry` -> `match_pattern`
6. `process_directory` -> `try_add_match`

See [srcs/parsing/wildcard/match/README.md](srcs/parsing/wildcard/match/README.md)
for the exact matching and directory-scan rules.