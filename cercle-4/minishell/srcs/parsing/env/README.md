# Env expansion package

This package contains the parsing-layer word expansion components. It
exposes two complementary entry points:

- `expand_tokens(t_nodes **tokens, char **env, int status)` — expand every
	`TOKEN_WORD` in a token list (tilde, parameter expansion, splitting,
	and globbing) and rebuild the token stream.
- `expand_and_split(char *str, char **env, int status)` — expand a single
	input word into a token list (used by `expand_tokens`).

The package is split into two focused submodules:

- `expand/` — token-list level expansion, wildcard handling, and match
	processing. Entry: `expand_tokens()`.
- `split/` — string-level expansion, dollar/tilde handling, quoting,
	backslash rules, and field splitting. Entry: `expand_and_split()`.

---

## How to use

1. Tokenize the input into a `t_nodes *` token list.
2. Call `expand_tokens(&tokens, envp, state->exit_code)` to perform full
	 word expansion on the token list.
3. If `expand_tokens` returns non-zero, an expansion error occurred (e.g.
	 ambiguous redirect); the caller should handle the error.

For single-word expansion (e.g. for redirection targets) call
`expand_and_split()` directly and interpret the returned list accordingly.

---

## Responsibilities

- The `split` submodule implements character-level rules: quotes, backslash
	escapes, `$` expansions, tilde handling, and splitting on unquoted
	whitespace.
- The `expand` submodule takes the list output, applies wildcard expansion
	via the `parsing/wildcard` API, detects ambiguous redirects, and
	reconstructs the final token stream.

Ancillary helpers (e.g. `apply_tilde_expansion`, `strip_glob_escapes`)
are shared between both submodules and live in `utils.c` and related
helpers.

---

## Folder-level call chains

1. `expand_tokens` -> `handle_word_node` -> `expand_and_split` ->
	 `process_expanded_list` -> `process_expanded_token` -> `expand_wildcard`
2. `expand_and_split` -> `run_expansion_loop` -> (`handle_dollar` /
	 `handle_backslash` / `handle_quote_split`) -> `process_val_split`

For module-level details see the submodule READMEs:

- `srcs/parsing/env/expand/README.md`
- `srcs/parsing/env/split/README.md`


