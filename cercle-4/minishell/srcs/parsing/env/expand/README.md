(Module) Word expansion and globbing

This subtree implements word expansion semantics used by the parser: tilde
expansion, parameter expansion, field splitting, and wildcard (glob)
matching. The layout below uses the same function-oriented, step-by-step
style as the reader documentation so callers can trace the exact call chains.

## Entry Path

`expand_tokens(t_nodes **tokens, char **env, int status)` in `tokens.c` is
the public entry point used to rewrite a token list after expansion.

The steps are:

1. Initialize an expansion context and iterate the original token list.
2. For non-word tokens, append them unchanged to the rebuilt list.
3. For `TOKEN_WORD` nodes, call `handle_word_node()` to perform tilde
	expansion, `expand_and_split()`, and post-processing.
4. After the loop, replace the original token list with the rebuilt head.
5. Return non-zero if expansion reported an error (e.g., ambiguous
	redirection), otherwise 0.

## Word expansion path

`handle_word_node()` (in `tokens.c`) performs the main word-expansion work.

The steps are:

1. If the previous token was a heredoc operator, skip expansion and append
	the token unchanged.
2. Call `apply_tilde_expansion(tok, env)` to replace leading `~`.
3. Call `expand_and_split(tok->value, env, status)` which returns a token
	list: the result of parameter expansion and field splitting.
4. Pass the returned list to `process_expanded_list()` for finalization.
5. Free the original token node.

`process_expanded_list()` iterates every produced token and calls
`process_expanded_token()`.

`process_expanded_token()` steps:

1. Mark the token type as `TOKEN_WORD`.
2. If the token is not quoted and `is_wildcard(token->value)` is true,
	call `expand_wildcard()` (in the wildcard subtree) to collect matches.
3. If matches are found, call `process_matches_or_literal()` to either
	insert matches or detect ambiguous redirection errors.
4. If no matches or the token is quoted, strip internal glob escape markers
	(`strip_glob_escapes`) and append the token node to the rebuilt list.

## Globbing and match handling

`process_matches_or_literal()` (in `match.c`) handles wildcard match lists.

The steps are:

1. Detect whether the expanded token is a redirection target by inspecting
	the previous token in the rebuilt list.
2. If it is a redirection target and more than one match exists, report
	`ambiguous redirect`, set the expansion error flag, and keep a literal
	token to preserve parse structure.
3. Otherwise convert each match into a token node (`create_token_node_from_match`)
	and append them to the rebuilt token list.

`consume_matches_to_list()` converts `t_nodes *matches` into token nodes and
releases the match list.

## Ancillary helpers

- `strip_glob_escapes(char *s)` removes internal escape markers used during
  pattern preparation.
- `is_prev_heredoc()` prevents changing heredoc delimiters.
- `expand_wildcard()` and low-level directory scanning live in the
  `parsing/wildcard` subtree; this module calls into that API.

## Memory and errors

- The module builds a new token list by reusing or freeing original nodes.
- On ambiguous redirects the function records `exp.expansion_error = 1` and
  returns an error code to the caller.
- All match lists are freed with `ft_lstclear(..., free)` after consumption.

## Folder-level call chains

1. `expand_tokens` -> `handle_word_node` -> `expand_and_split` ->
	`process_expanded_list` -> `process_expanded_token` -> `expand_wildcard`
2. `process_expanded_token` -> `process_matches_or_literal` ->
	`consume_matches_to_list`

For exact signatures and edge cases, see `tokens.c` and `match.c` in this
directory and the wildcard helpers in `srcs/parsing/wildcard`.

