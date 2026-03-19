# Input Reader Pipeline

This directory contains the functions that read one command line from either an
interactive terminal or standard input, detect whether the line is incomplete,
request continuation lines when needed, and return one fully assembled command
string to the core loop. The flow below is function-oriented and follows the
exact calls in this subtree.

## Entry Path

`get_command_line` in `reader.c` is the entry point used by the shell main
loop.

The steps are:

1. Call `get_prompt(1)` to resolve the main shell prompt.
2. Call `read_input(prompt, state)`.
3. If `read_input` returns `NULL`, propagate `NULL` to the caller.
4. Otherwise return the fully assembled command line.

This is the function called by the core runtime before every `process_input`
step.

## Raw Read Path

`read_input` in `reader.c` performs one logical read operation.

The steps are:

1. Call `read_raw_input(prompt, state)`.
2. If `read_raw_input` returns `NULL`, propagate EOF immediately.
3. Otherwise pass the line to `handle_multiline_input(line, state)`.
4. Return the resulting complete line.

`read_raw_input` selects the actual source of the first line.

Its routing is exact:

- when stdin is a tty, read with `readline(prompt)`
- otherwise read with `get_next_line(STDIN_FILENO)`

That split is what lets the shell support both interactive prompts and
non-interactive stdin-driven execution.

## Multiline Continuation Path

`handle_multiline_input` in `multiline.c` keeps reading until the current input
is syntactically complete for the reader layer.

The steps are:

1. Fetch the operator definition table through `get_ops()`.
2. Call `ext_analyze_input(line)`.
3. If the returned code is `0`, stop and return the current line.
4. Otherwise store the current line and continuation code in `t_line_struct`.
5. Call `read_next_line_and_append(&ls, ops, state)`.
6. Repeat until `ext_analyze_input` reports a complete line or a read fails.

`read_next_line_and_append` performs one continuation step.

The steps are:

1. Build the continuation prompt with `get_multiline_prompt(ls->code, ops)`.
2. Call `read_and_append_line(ls, ops, state)`.
3. Free the temporary continuation prompt.
4. Return the combined line.

`get_multiline_prompt` uses `ext_get_op_def(ops, code)` to look up the label
associated with the missing construct.

Its rules are:

- when a matching operator definition has a label, build `label + "> "`
- otherwise fall back to `get_prompt(0)`

`read_and_append_line` then performs the actual continuation read.

The steps are:

1. Read the next physical line through `read_raw_input(ls->prompt, state)`.
2. If EOF occurs:
   - resolve the operator definition with `ext_get_op_def`
   - print either the matching-delimiter error or the generic unexpected EOF
     syntax error
   - set `state->syntax_error = 1`
   - free the accumulated line
   - return `NULL`
3. Otherwise merge the accumulated line and the new line through
   `append_line(ls->line, new_line, ls->code)`.
4. Free the old buffers and return the merged line.

## Line Merge Path

`append_line` in `utils.c` joins one continuation line to the accumulated input.

The steps are:

1. Reject null inputs.
2. Walk backward from the end of the current line, skipping trailing
   whitespace.
3. If the continuation code is `\\` and the last significant character is a
   backslash, call `append_with_backslash`.
4. Otherwise call `append_with_newline`.

`append_with_backslash` removes the active trailing backslash before joining the
new line, which preserves shell line-continuation semantics.

`append_with_newline` inserts a literal newline between both pieces before
joining them.

## Prompt And Operator Helpers

`get_prompt` in `utils.c` resolves the prompt string used by the reader.

Its rules are:

- when stdin is not interactive, return `NULL`
- when `is_initial` is non-zero, return `"minishell> "`
- otherwise return `"> "`

`get_ops` in `operations.c` returns the static definition table used by the
reader and extender layers.

That table maps continuation codes to:

- the triggering symbol
- the prompt label
- the expected counterpart when one exists

`ext_get_op_def` searches that table by continuation code and returns the
matching definition.

## Extender Handoff

The reader layer does not decide continuation rules itself.
It delegates that decision to `ext_analyze_input` in the `extenders`
subdirectory.

That submodule is responsible for:

- unmatched quote detection
- unmatched parenthesis detection
- trailing operator detection
- trailing backslash continuation detection

See `srcs/input/reader/extenders/README.md` for the exact continuation-analysis
pipeline.

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `get_command_line` -> `get_prompt` -> `read_input`
2. `read_input` -> `read_raw_input` -> `handle_multiline_input`
3. `handle_multiline_input` -> `ext_analyze_input` ->
   `read_next_line_and_append`
4. `read_next_line_and_append` -> `get_multiline_prompt` ->
   `read_and_append_line`
5. `read_and_append_line` -> `read_raw_input` -> `append_line`
6. `append_line` -> `append_with_backslash` or `append_with_newline`
