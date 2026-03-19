# Input Reader Pipeline

This subtree reads one logical command line from the user or stdin, detects
incomplete constructs (unclosed quotes, parentheses, trailing operators or an
active backslash), and prompts for continuation until the input is complete.
The README follows the function-level call flow implemented in this folder.

## Entry Path

`get_command_line(state)` in `reader.c` is the public entry used by the main
loop. It obtains the prompt (`get_prompt(1)`), calls `read_input()` and
returns a fully assembled command line or `NULL` on EOF.

## Raw Read Path

`read_input(prompt, state)` performs the initial physical read via
`read_raw_input()` and delegates continuation handling to
`handle_multiline_input()`.

`read_raw_input()` chooses the source:
- interactive: `readline(prompt)`
- non-interactive: `get_next_line(STDIN_FILENO)`

This split allows the shell to work both as an interactive prompt and as a
non-interactive stdin-driven program.

## Multiline Continuation Path

`handle_multiline_input(line, state)` loops until `ext_analyze_input()`
returns `0` (line complete). When a continuation code is returned the loop:

1. Stores the current buffer in a `t_line_struct` and computes the next
   continuation prompt via `get_multiline_prompt(code, ops)`.
2. Calls `read_and_append_line()` to read one physical continuation line and
   merge it with the accumulated buffer using `append_line()`.
3. Repeats the analysis on the merged buffer.

`read_and_append_line()` handles EOF diagnostics: when EOF occurs it prints
either a matching-delimiter message or a generic unexpected EOF error,
sets `state->syntax_error`, frees the accumulated buffer and returns `NULL`.

## Line Merge Path

`append_line(line, new_line, code)` merges the accumulated input and the
fresh continuation line. Rules:
- If the continuation code is `'\\'` and the last non-space char is a
  backslash, the active backslash is removed and pieces are concatenated
  (`append_with_backslash`).
- Otherwise a literal newline is inserted between the pieces
  (`append_with_newline`).

`find_last_non_space()` is used to locate the last significant character in
the current buffer.

## Prompt & Operator Helpers

`get_prompt(is_initial)` returns the interactive prompt strings when stdin is
a TTY; `get_ops()` returns the static operator-definition table used by the
extenders; `ext_get_op_def()` resolves a continuation code into its
definition (symbol, label, counterpart).

## Extender Handoff

Continuation detection is implemented in the `extenders/` submodule. Call
flow:

1. `ext_analyze_input(line)` → checks pairs (`ext_scan_pairs_state`) then
   trailing operators (`check_trailing_op`).
2. When continuation is needed, `get_multiline_prompt()` uses the op-table
   label to build a user-friendly prompt.

See `srcs/input/reader/extenders/README.md` for the exact continuation rules
and codes.

## Folder-Level Call Chains

1. `get_command_line` -> `get_prompt` -> `read_input`
2. `read_input` -> `read_raw_input` -> `handle_multiline_input`
3. `handle_multiline_input` -> `ext_analyze_input` ->
   `read_next_line_and_append`
4. `read_next_line_and_append` -> `get_multiline_prompt` ->
   `read_and_append_line`
5. `read_and_append_line` -> `read_raw_input` -> `append_line`
6. `append_line` -> `append_with_backslash` or `append_with_newline`

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
