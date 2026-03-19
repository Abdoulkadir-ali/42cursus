# input/process

Purpose
- Handle tokenized input segments: build semicolon-delimited segments,
  detect standalone assignments, prepare heredocs, build ASTs and execute
  segments.

Overview
- This directory implements the high-level processing pipeline that runs after
  tokenization and syntax validation. It turns token lists into executable
  actions, performing these responsibilities:
  - segmenting token streams by semicolon
  - detecting and applying simple `KEY=VALUE` assignments
  - preparing heredocs and executing the resulting AST

Key files
- `exec.c` — `execute_ast()` builds an AST from a segment, prepares heredocs,
  runs `exec_tree()` and sets `state->exit_code` according to execution result
  and signals.
- `process.c` — `process_input()` is the public entry: tokenizes the raw line,
  runs syntax checks, iterates semicolon-separated segments and dispatches
  them for execution or assignment handling.
- `segment.c` — helpers for identifying assignment-only segments and
  applying them (`try_handle_assignment_public()`), plus key extraction.
- `utils.c` — small helpers: `is_whitespace_only()`, `build_segment_until_semicolon()`
  and `consume_semicolon_if_present()`.

Typical flow
1. `process_input(line, state)` called by the reader.
2. Tokenize and run `check_syntax()`; bail out on failure.
3. Split tokens into semicolon-delimited segments.
4. For each segment:
   - If it's a single `KEY=VALUE` assignment, apply it to the shell state.
   - Otherwise, call `execute_ast()` to build the AST, scan/prepare heredocs
     and run the execution tree.

Notes for contributors
- `try_handle_assignment_public()` enforces identifier validity and single-token
  segments before treating a segment as an assignment.
- `execute_ast()` sets up signal modes around heredoc scanning and child
  execution; tests should assert correct `state->exit_code` behavior on
  heredoc cancellation and signal conditions.

Ownership
- Many helpers return or manipulate `t_nodes *` lists in-place — callers must
  free nodes and token contents using the provided `del_token()` helper when
  consuming or discarding token lists.
# Input Process Pipeline

This directory contains the functions that transform one raw input line into
semicolon-delimited execution segments, apply variable-assignment shortcuts,
expand tokens, build the AST, prepare heredocs, and hand execution to the exec
layer. The flow below is function-oriented and follows the exact calls in this
subtree.

## Entry Path

`process_input` in `process.c` is the entry point for one line received from
the input reader.

The steps are:

1. Reject the line immediately when it is empty or `is_whitespace_only(line)`.
2. If the shell is interactive, add the line to readline history.
3. Call `tokenize_and_check(line, state)`.
4. If tokenization or syntax validation fails:
   - keep the exit status already stored in `state->exit_code`
   - exit immediately in non-interactive mode
   - otherwise return to the caller
5. If tokenization succeeds, call `process_segments(tokens, state)`.

## Tokenization And Syntax Path

`tokenize_and_check` in `process.c` converts the raw line into validated tokens.

The steps are:

1. Call `tokenizer(line)`.
2. If tokenization fails, store exit status `2` and return `NULL`.
3. Call `check_syntax(tokens)`.
4. If syntax checking fails:
   - store the reported status in `state->exit_code`
   - call `consume_heredocs(tokens, state)` to pre-handle pending heredocs
   - clear the token list
   - return `NULL`
5. Otherwise return the validated token list.

## Segment Split Path

`process_segments` in `process.c` iterates through the validated token list one
semicolon-delimited segment at a time.

The steps are:

1. Start from the first token with `cursor = tokens`.
2. Call `extract_segment(cursor, &next_cursor)`.
3. `extract_segment` delegates the split to `build_segment_until_semicolon`.
4. `build_segment_until_semicolon` detaches token nodes until it reaches a
   `TOKEN_SEMICOLON` or the end of the stream.
5. `extract_segment` then calls `consume_semicolon_if_present(it, pnext)`.
6. `consume_semicolon_if_present` removes the semicolon node when one is
   present and exposes the next segment start.
7. `process_segments` then decides how to handle the extracted segment.

## Assignment Shortcut Path

Before full expansion and AST execution, `process_segments` tries the direct
assignment fast path through `try_handle_assignment_public(segment, state)`.

The steps are:

1. `try_handle_assignment_public` checks `is_assignment_segment(segment)`.
2. `is_assignment_segment` accepts only a segment whose first token is a
   `TOKEN_WORD` containing `=` and not starting with `=`.
3. `try_handle_assignment_public` rejects the fast path when the identifier is
   invalid or when the segment contains more than one token.
4. For a valid standalone assignment, `extract_key_value` splits the token into
   key and value strings.
5. `set_assignment` calls `ft_set_env(key, val, state)`.
6. `set_assignment` also sets `state->exit_code = 0`.
7. The segment list is cleared and the function returns `1`.

If this path succeeds, the segment never reaches expansion or AST execution.

## Expansion And Execution Path

When the assignment shortcut does not consume the segment, `process_segments`
calls `process_segment_internal(segment, state)`.

The steps are:

1. `process_segment_internal` calls `expand_and_check_error(&segment, state,
   &state->exit_code)`.
2. `expand_and_check_error` expands the token list through `expand_tokens`.
3. If expansion sets `state->expansion_error`, the segment is cleared,
   `state->exit_code` is preserved, the error flag is reset, and the function
   returns `1`.
4. If expansion succeeds, `process_segment_internal` calls `execute_ast`.
5. `execute_ast` builds the AST through `ast_builder(segment)`.
6. It then materializes heredocs with `scan_heredocs(ast, state)`.
7. If heredoc scanning succeeds, it executes the AST through `exec_tree(ast,
   state)` and stores the returned status in `state->exit_code`.
8. If heredoc scanning fails, it maps the failure to `130` when `g_last_signal
   == 130`, otherwise to `1`.
9. Finally `execute_ast` releases the AST with `free_ast(ast)`.

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `process_input` -> `tokenize_and_check` -> `process_segments`
2. `process_segments` -> `extract_segment` -> `build_segment_until_semicolon`
3. `extract_segment` -> `consume_semicolon_if_present`
4. `process_segments` -> `try_handle_assignment_public` ->
   `is_assignment_segment` -> `extract_key_value` -> `set_assignment`
5. `process_segments` -> `process_segment_internal` ->
   `expand_and_check_error` -> `execute_ast`
6. `execute_ast` -> `ast_builder` -> `scan_heredocs` -> `exec_tree`