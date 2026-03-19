# parsing/wildcard/match

Purpose
- Low-level helpers implementing wildcard (glob) pattern matching and
  directory-entry collection used by the wildcard expansion subsystem.

Overview
- `loop.c` contains the core matching engine:
  - `is_wildcard(const char *str)` — detect whether a pattern still has
    active metacharacters (`*` or `?`). The function skips escaped bytes
    encoded as `\001` pairs before checking for metacharacters.
  - `match_loop(char **pattern, char **str, char **star, char **str_start)` —
    runs the matching loop with support for `*` backtracking and `?` single-
    character matches. Helper subroutines manage star positions, advancing
    both cursors, and backtracking when needed.

- `helpers.c` provides pattern preparation and entry-level checks:
  - `prepare_pattern(char *pattern, int *require_dir)` — duplicates the
    original pattern and normalizes trailing slashes into a `require_dir` flag
    (if pattern ends with `/`, only directories may match).
  - `should_skip_entry(struct dirent *entry, char *pattern)` — rejects
    entries that must never match (dotfiles when pattern doesn't start with
    `.`, `.` and `..`, or exact-string duplicates of the pattern).
  - `match_pattern(char *pattern, char *str)` — public predicate that calls
    the `match_loop` engine and ensures the whole pattern is consumed.
  - `check_entry(struct dirent *entry, char *pat_copy, int require_dir)` —
    runs `should_skip_entry`, `match_pattern` and, when `require_dir` is set,
    verifies the entry is a directory (using `d_type` or a `stat` fallback).
  - `try_add_match()` — safe append of a matching filename into a result
    list, with a cap to avoid unbounded allocations.

- `match.c` provides higher-level directory scanning and collection:
  - `process_directory(DIR *dir, char *pat_copy, int require_dir)` — iterate
    over `readdir()` entries, call `check_entry()` and accumulate matching
    names into a `t_nodes *` list.
  - `collect_matches(DIR *dir, char *pattern)` — convenience wrapper that
    prepares the pattern via `prepare_pattern`, calls `process_directory`,
    and frees the temporary pattern copy.

Behavior notes
- Dotfile handling: names beginning with `.` are only matched when the
  pattern explicitly begins with `.` (the code recognizes an encoded `\001`
  prefix too).
- Trailing slash: patterns ending in `/` are normalized and mark `require_dir`.
- Backtracking: `match_loop` supports classic `*` backtracking to find the
  longest matching span consistent with the remainder of the pattern.
- Safety caps: the code limits stored matches and iteration counts to avoid
  pathological allocations when directories contain many entries.

Usage
- Call `collect_matches(dir, pattern)` to obtain a `t_nodes *` list of
  matching filenames (caller must free the list and strings). The returned
  names are raw directory entry names and must be joined with a path prefix
  by the caller if needed.

See also
- `srcs/parsing/wildcard/expand.c` — higher-level expansion pipeline that uses
  `collect_matches()` to expand tokens containing active wildcard metacharacters.
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