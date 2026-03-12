# Heredoc Execution Pipeline

This directory contains the functions that prepare heredocs and here-strings
before execution, then read and expand their contents into temporary files. The
flow below is function-oriented and follows the exact calls in this subtree.

## AST Scan Entry

`scan_heredocs` in `scan.c` is the entry point used to materialize heredoc-like
nodes before normal execution.

Its routing is exact:

- when `ast_node->type == TOKEN_HEREDOC`, call `handle_heredoc_input`
- replace `ast_node->args[0]` with the returned temporary filename
- free any quoted-flag argument in `ast_node->args[1]`
- rewrite the node type to `TOKEN_RED_IN`
- when `ast_node->type == TOKEN_HERESTR`, call `handle_herestr`
- recurse into `ast_node->left` and `ast_node->right`

If any heredoc preparation fails, `scan_heredocs` returns `1`.

## Here-String Path

`handle_herestr` in `scan.c` converts a here-string into a regular input
redirection backed by a temporary file.

The steps are:

1. Allocate a temporary file with `create_tmp_file(&fd, &tmp_file)`.
2. Call `write_herestr(node, state, fd)`.
3. `write_herestr` resolves the payload with `get_herestr_word`.
4. `get_herestr_word` reads `node->args[0]`, checks the quoted flag in
   `node->args[1]`, and expands the text through `expand_delim` when quoting
   does not forbid it.
5. Write the resolved text and one trailing newline into the temp file.
6. Replace `node->args[0]` with the temporary filename.
7. Clear `node->args[1]` and rewrite `node->type` to `TOKEN_RED_IN`.

## Direct Heredoc Input Path

`handle_heredoc_input` in `input.c` prepares the temporary file that will later
be opened as stdin.

The steps are:

1. Resolve the delimiter with `get_heredoc_delim(args, state, &quoted)`.
2. `get_heredoc_delim` reads `args[0]`, extracts the quoted flag from
   `args[1]`, and expands the delimiter through `expand_delim` when quoting is
   disabled.
3. Call `write_heredoc_to_file(delim, state, quoted)`.
4. `write_heredoc_to_file` allocates a temp file with `generate_tmp_filename`.
5. It then runs `read_heredoc_loop(delim, fd, state, quoted)`.
6. On success it returns the temp filename.
7. If `g_last_signal == 130`, remove the temp file and return `NULL`.

## Token-List Consumption Path

`consume_heredocs` in `consume.c` performs the same heredoc pre-consumption on
the token list representation.

The steps are:

1. Iterate through the token list.
2. Call `process_heredoc(tokens, state)` for each node.
3. `process_heredoc` checks whether the current token is `TOKEN_HEREDOC`.
4. If the next token exists and is `TOKEN_WORD`, call
   `handle_heredoc_word(next_tok, state)`.
5. `handle_heredoc_word` expands the delimiter when needed, creates a temp
   file, runs `read_heredoc_loop`, then closes and unlinks the file.

This path consumes the heredoc for validation and signal handling before the
later execution phase.

## Read Loop Path

`read_heredoc_loop` in `read.c` drives the line-by-line heredoc read.

The steps are:

1. Build the effective stop string with `prepare_stop_str(delim, &ctx)`.
2. If the caller did not already mark the delimiter as quoted, recompute it
   with `is_quoted_delim(delim)`.
3. Switch signal handling to `SIGNAL_HEREDOC`.
4. Call `read_heredoc_lines(stop_str, is_quoted, &ctx)`.
5. Restore `SIGNAL_INTERACTIVE`.
6. Free the stop string.

`read_heredoc_lines` loops until one of three events occurs:

1. `heredoc_read_line()` returns `NULL`, which triggers
   `handle_heredoc_eof(stop_str)`.
2. `process_heredoc_line(line, stop_str, quoted, ctx)` returns `1` because the
   delimiter was reached.
3. A signal interrupts the read path and the caller later observes it through
   `g_last_signal`.

`process_heredoc_line` routes each line to one of two handlers:

- `process_line_quoted` when expansion is disabled
- `process_line_unquoted` when expansion is enabled

`process_line_quoted` trims the line only for stop-string comparison, writes
the original line to the temp file when it is not the delimiter, and returns
`1` only on delimiter match.

`process_line_unquoted` expands the line with `expand_heredoc`, trims the
expanded result for comparison, writes the expanded line when it is not the
delimiter, and returns `1` only on delimiter match.

`handle_heredoc_eof` reports the standard shell warning when EOF arrives before
the stop string, except when the heredoc was interrupted by `SIGINT`.

## Delimiter Preparation Path

`prepare_stop_str` in `read.c` computes the string compared against every
incoming heredoc line.

The rules are:

- if the delimiter is quoted, remove the quotes with `remove_quotes_heredoc`
- if the quoted delimiter contained a double quote, expand the unquoted result
  with `expand_string`
- if the delimiter is not quoted, expand it directly with `expand_string`
- if any expansion step fails, fall back to `ft_strdup(delim)`

`expand_delim` is the lighter helper used by node preparation and here-strings.
It returns the original delimiter pointer when quoting forbids expansion, and
otherwise expands the text with `expand_heredoc`.

## Quote Removal Path

`remove_quotes_heredoc` in `quotes.c` strips shell quotes and escaped
characters from a delimiter.

The steps are:

1. Allocate a destination buffer as large as the input.
2. Scan each source character with `t_quotes_state`.
3. While inside quotes, let `handle_inside_quote` either close the quote or
   copy the literal character.
4. While outside quotes, let `handle_outside_quote` consume backslash escapes,
   enter quote mode, or copy plain characters.
5. Terminate the destination string and return it.

`is_quoted_delim` detects whether any quote semantics exist in the raw
delimiter, and `generate_tmp_filename` creates the temporary heredoc file with
`mkstemp`.

## Expansion Helpers

`expand_string` in `expand.c` performs the general expansion pass used for stop
string preparation.

The steps are:

1. Initialize a `t_expansion` context.
2. Iterate across the source string.
3. At each position call `process_expand_char(&exp)`.
4. `process_expand_char` tries backslash, quote, and dollar handlers in order.
5. If no handler consumes the character, append it literally.
6. Return the fully expanded output string.

`expand_heredoc` is the simpler line-expansion helper used for heredoc content.
It only expands `$?` and shell variables whose names satisfy `is_var_char`.

## Input Source Path

`heredoc_read_line` in `utils.c` selects the actual input source.

Its routing is exact:

- when stdin is a tty, read with `readline("> ")`
- otherwise call `heredoc_read_line_non_tty()`

`heredoc_read_line_non_tty` reads one line through `get_next_line`, strips the
trailing newline when present, and returns the resulting string.

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `scan_heredocs` -> `handle_heredoc_input` -> `read_heredoc_loop`
2. `scan_heredocs` -> `handle_herestr` -> `write_herestr` -> `get_herestr_word`
3. `consume_heredocs` -> `process_heredoc` -> `handle_heredoc_word` ->
   `read_heredoc_loop`
4. `read_heredoc_loop` -> `prepare_stop_str` -> `read_heredoc_lines` ->
   `process_heredoc_line`
5. `process_heredoc_line` -> `process_line_quoted` or
   `process_line_unquoted`