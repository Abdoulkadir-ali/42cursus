# Env Expansion Pipeline

This directory contains the functions that rewrite token lists after variable,
tilde, and field-splitting expansion, then apply wildcard expansion where
appropriate. The flow below is function-oriented and follows the exact calls in
this subtree.

## Entry Path

`expand_tokens` in `tokens.c` is the public entry point for token expansion.

The steps are:

1. Initialize a `t_token_expansion` context.
2. Iterate over the original token list one node at a time.
3. For `TOKEN_WORD`, call `handle_word_node(&exp, curr, env, status)`.
4. For every other token type, append the node unchanged to the rebuilt list.
5. Keep `exp.prev` synchronized with the last appended node.
6. Replace `*tokens` with the rebuilt list head.
7. Return `exp.expansion_error`.

## Word Expansion Path

`handle_word_node` processes one word token.

Its routing is exact:

1. If the previous token is a heredoc operator, keep the word unchanged.
2. Otherwise apply tilde expansion through `apply_tilde_expansion(tok, env)`.
3. Expand and split the token text through `expand_and_split(tok->value, env,
   status)`.
4. Pass the resulting token list to `process_expanded_list`.
5. Delete the original token node after the expanded list has taken over.

The heredoc check matters because heredoc delimiters must not go through the
normal word-expansion path.

## Expanded List Path

`process_expanded_list` consumes the token list returned by
`expand_and_split`.

The steps are:

1. Iterate over every expanded token node.
2. Pass each node to `process_expanded_token`.
3. Let that helper decide whether the token stays literal or triggers wildcard
   matching.

## Wildcard Path

`process_expanded_token` decides whether wildcard expansion applies.

The rules are:

- force the expanded token type to `TOKEN_WORD`
- if the token is quoted, skip wildcard matching
- if the token is not quoted and `is_wildcard(exp_tok->value)` is true, call
  `expand_wildcard(exp_tok->value)`
- when wildcard matches exist, pass them to `process_matches_or_literal`
- when no wildcard matches exist, strip internal glob escape markers and keep
  the token literally

`strip_glob_escapes` removes the internal `\001` markers used during glob
preparation.

## Match-Conversion Path

`process_matches_or_literal` in `match.c` handles the list returned by
`expand_wildcard`.

The steps are:

1. Check whether the current token is the target of a redirection by looking at
   `exp->prev`.
2. `is_redir_token_type` recognizes `TOKEN_RED_OUT`, `TOKEN_APPEND`, and
   `TOKEN_RED_IN` as redirection operators.
3. If the current token is a redirection target and the wildcard produced more
   than one match, report `ambiguous redirect`, set `exp->expansion_error`, and
   keep the original token node in the rebuilt stream.
4. Otherwise convert every matched string into a token node through
   `consume_matches_to_list`.

`count_match_nodes` counts the wildcard matches for the ambiguous-redirect
check.

`consume_matches_to_list` performs the actual replacement.

The steps are:

1. Iterate over the linked list of matched strings.
2. Convert each string into a token node with `create_token_node_from_match`.
3. Append the resulting nodes to the rebuilt token list.
4. Clear the temporary match list.
5. Delete the original expanded token node that has now been replaced.

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `expand_tokens` -> `handle_word_node`
2. `handle_word_node` -> `apply_tilde_expansion` -> `expand_and_split` ->
   `process_expanded_list`
3. `process_expanded_list` -> `process_expanded_token`
4. `process_expanded_token` -> `expand_wildcard` ->
   `process_matches_or_literal`
5. `process_matches_or_literal` -> `count_match_nodes` or
   `consume_matches_to_list`