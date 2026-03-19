# 🧠 Parsing Module

# Parsing Module

> Transforms raw user input into structured commands the shell can execute.

The parsing package performs lexical analysis, variable and wildcard expansion,
AST construction and syntax validation. Submodules are intentionally small and
focused so the parser remains testable and easy to refactor.

---

## Layout
- `ast/` — AST builder and node utilities.
- `env/` — environment expansion and splitting (tilde, `$`, quoting rules).
- `tokenizer/` — tokenization, token helpers and syntax validation.
- `wildcard/` — glob matching, collection and sorting helpers.

Each directory contains a README with details on responsibilities and call
flows; see the submodule READMEs for implementation specifics.

---

## ast/
Purpose
- Build the `t_ast` tree representing commands, pipelines, redirections and
	subshells. Exposes helpers to consume token lists and produce executable
	AST nodes.

Key files
- `builder.c` — orchestration: walks tokens and constructs nodes.
- `cmd/` — command-specific builders (prefixes, arguments, redirections).
- `subshell.c`, `redirections.c`, `utils.c` — node helpers and cleanup.

Flow (high level)
- Token list → scan/collect → create nodes → validate AST → hand to exec.

---

## env/
Purpose
- Expand variables and manage word-splitting while respecting quotes and
	shell semantics. Provides a single expansion pipeline used by parsing and
	execution.

Key files
- `expand/` — variable expansion, wildcard escape handling.
- `split/` — field-splitting after expansion.

Notes
- Expansion functions return owned `char **` arrays or token lists; callers
	must follow ownership/freeing conventions.

---

## tokenizer/
Purpose
- Convert input strings into `t_token` objects, classify token types, and run
	a lightweight syntax pass to reject invalid sequences before AST creation.

Key files
- `tokenizer.c` — main lexer and dispatch to handlers.
- `handlers/` — word/operator handlers creating tokens.
- `syntax/` — sequence validators and helpful error reporting.

Flow
- Raw input → tokenize (respecting quotes/escapes) → syntax check → tokens
	returned for AST building.

---

## wildcard/
Purpose
- Match `*`/`?` patterns against the filesystem, collect matches and sort
	results for insertion into argument lists.

Key files
- `match/` — low-level pattern matching and directory-entry checks.
- `expand.c` — public entry `expand_wildcard()`.
- `sort.c` — in-place ordering of match lists.

Behavior
- Dotfile rules, trailing-slash directory requirements and caps on stored
	matches are enforced to match common shell expectations.

---

## Developer notes
- Keep parsing helpers small and side-effect free when possible.
- Use `token_list_to_array()` and `free_string_array()` for safe array
	conversions and ownership transfer.
- When refactoring expansion, prefer exposing a minimal API used by `exec` so
	parsing remains the single source of truth for expansion semantics.

For implementation details, consult the submodule READMEs and the headers in
`includes/parsing.h`.
- `tokenizer/`: Tokenizes input strings, checks syntax, and prepares tokens for parsing.
