# AST Submodule

This directory builds the Abstract Syntax Tree (AST) from token lists so the
execution subsystem receives well-formed command structures. The layout and
style below follow the reader subsystem documentation: function-oriented,
step-by-step, and easy to trace back to source files.

## Entry Path

`build_ast` (in `builder.c`) is the public entry used by the core after the
tokenizer and expansion phases have produced a token list.

The steps are:

1. Call `builder_init()` to initialize internal builder state.
2. Iterate over the token list, calling `parse_pipeline()` for each pipeline
   segment.
3. For each pipeline element, call the appropriate handler: `handle_simple_cmd`
   for simple commands, `handle_subshell` for parenthesized groups, etc.
4. Link produced `t_ast` nodes into pipelines and lists per syntax.
5. Validate the constructed AST and return the root node to the caller.

This function is the primary handoff from parsing to execution.

## Command node path (ast/cmd)

Simple commands are processed through the `ast/cmd` helpers (see the
`ast/cmd` subtree). The high-level flow for a command segment is:

1. `scan_command_tokens()` counts words and assignment prefixes.
2. `collect_prefixes()` and `build_args_from_tokens()` duplicate strings.
3. `handle_simple_cmd()` creates the command `t_ast` node and calls
   `process_redirections()` to attach redirections.

See `ast/cmd/README.md` for a detailed step-by-step of that path.

## Subshell path

`handle_subshell()` (in `subshell.c`) builds an AST for parenthesized
expressions:

1. Consume the opening `(` token.
2. Recurse into `build_ast()` or `parse_list()` to build the inner AST.
3. Expect and consume the closing `)` token, report a syntax error on EOF.
4. Return a `t_ast` node representing the subshell.

## Redirections

Redirection handling is centralized in `redirections.c` and integrates with
both `handle_simple_cmd()` and subshell finalization.

Redirection processing steps (summary):

1. Walk the token segment looking for redirection operators.
2. For each operator, consume the next token as the target and build a
   redirection AST node.
3. Attach redirection nodes to the command or subshell node.
4. On ambiguous expansions or missing targets, set `state->syntax_error` and
   return `NULL`.

## AST utilities and cleanup

`utils.c` and `utils_*` helpers provide node allocation, linking, and
freeing. Typical helpers:

- `create_node()` — allocate and initialize a `t_ast` node.
- `append_node()` — append nodes to lists/pipelines.
- `free_ast()` — recursively free an AST and its resources.

## Error handling

- Parsing functions return `NULL` on failure and set `state->syntax_error`
  when appropriate.
- Functions that allocate intermediate resources (arrays, nodes) free
  partially created state on error before returning `NULL`.

## Folder-level call chains

Common flows used by the parser:

1. `build_ast` -> `parse_pipeline` -> `handle_simple_cmd` ->
   `scan_command_tokens` / `collect_prefixes` / `build_args_from_tokens`
2. `build_ast` -> `parse_pipeline` -> `handle_subshell` -> `build_ast`
3. `handle_simple_cmd` -> `process_redirections`

For exact function signatures and detailed behavior, see the source files in
this directory: `builder.c`, `cmd/`, `redirections.c`, and `subshell.c`.
