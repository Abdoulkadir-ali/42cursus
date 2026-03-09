# Input Module

Handles all user input processing, segmentation, and reading logic for the shell. This subsystem is responsible for capturing, parsing, and preparing command lines for further parsing and execution.

---

## 📂 Directory Structure
- `srcs/input/` — Input processing root
  - `process/` — Segmentation and preprocessing of input lines
  - `reader/` — Interactive and multiline input reading, operations, and extenders

---

## 🏗️ How It Works

### Global Pipeline
1. The core loop asks the input layer for the next command through `get_command_line(state)`.
2. The reader submodule chooses the prompt and reads the first physical line from either `readline` or standard input.
3. The reader then checks whether the line is incomplete because of unmatched quotes, unmatched parentheses, trailing operators, or a trailing backslash.
4. If continuation is required, the reader keeps collecting extra lines and merges them into one logical command line.
5. Once the line is complete, the process submodule tokenizes it and validates shell syntax.
6. The validated token stream is split into semicolon-delimited segments.
7. Each segment is either consumed as a standalone assignment or expanded, converted into an AST, scanned for heredocs, and handed to the execution layer.
8. The resulting command status is written back into `state->exit_code` for the core loop.

### `process/`
- **process.c**: Implements input segmentation logic. Splits raw input into command segments, handles chaining (e.g., `;`, `&&`, `||`), and prepares for tokenization.
- **segment.c**: Defines segment structures and helpers. Groups tokens into logical command segments.
- **utils.c**: Utility functions for segment manipulation, error handling, and context management.

#### Pipeline Inside `process/`
1. `process_input` is the entry point for one logical line returned by the reader.
2. It rejects empty or whitespace-only lines before doing any work.
3. In interactive mode it records the line in history.
4. It calls `tokenize_and_check` to build the token list and run `check_syntax`.
5. If syntax validation fails, pending heredocs are pre-consumed through `consume_heredocs`, the token list is cleared, and non-interactive mode exits immediately with the stored status.
6. If tokenization succeeds, `process_segments` walks the token list one semicolon-delimited segment at a time.
7. `extract_segment`, `build_segment_until_semicolon`, and `consume_semicolon_if_present` detach each segment from the token stream.
8. `try_handle_assignment_public` handles standalone `KEY=VALUE` segments directly through `ft_set_env`.
9. Any remaining segment flows through `process_segment_internal`.
10. `process_segment_internal` expands tokens with `expand_and_check_error`, builds the AST through `ast_builder`, materializes heredocs through `scan_heredocs`, and finally executes the AST through `exec_tree`.

---

### `reader/`
- **reader.c**: Main reader entry points. Selects the prompt, reads the first physical line, and returns one logical command line.
- **multiline.c**: Continues reading when the current line ends in an incomplete construct.
- **operations.c**: Defines the continuation operator table used by the reader and extender logic.
- **utils.c**: Helper functions for prompt resolution and line merging.
- **extenders/**: Detects unmatched delimiters and trailing operators that require continuation.

#### Pipeline Inside `reader/`
1. `get_command_line` starts the read path.
2. It resolves the initial prompt with `get_prompt(1)`.
3. It then calls `read_input(prompt, state)`.
4. `read_input` reads the first physical line through `read_raw_input`.
5. `read_raw_input` uses `readline(prompt)` when stdin is interactive and `get_next_line(STDIN_FILENO)` otherwise.
6. The initial line is passed to `handle_multiline_input`.
7. `handle_multiline_input` repeatedly calls `ext_analyze_input` from the `extenders` subdirectory.
8. When continuation is required, it builds a specialized continuation prompt with `get_multiline_prompt`, reads another physical line, and merges it with `append_line`.
9. `append_line` removes an active trailing backslash when continuation was requested by `\\`, otherwise it joins lines with a literal newline.
10. When the line is complete, the reader returns one fully assembled command string to `process_input`.

#### Extender Handoff
1. The `reader/` layer does not decide continuation rules itself.
2. It delegates that decision to `ext_analyze_input` in `reader/extenders`.
3. The extender logic checks unmatched quotes, unmatched parentheses, trailing operators, and lone trailing backslashes.
4. The returned continuation code drives both the continuation prompt and the line-merge behavior.

---

## 🛠️ Developer Notes
- The input module is split cleanly into two stages: line acquisition in `reader/` and command preparation in `process/`.
- The reader always returns one logical command line, even when that requires multiple physical reads.
- Syntax checking happens before AST building, and syntax failures still pre-consume pending heredocs so error handling matches shell behavior.
- Standalone assignments are intercepted before AST execution, which keeps environment-only updates out of the normal command pipeline.
- Heredoc preparation is triggered from the input-process stage, but the actual materialization work is delegated to the execution-side heredoc helpers.

For detailed function documentation, see the source files and header definitions in `includes/input.h` and submodule headers.
