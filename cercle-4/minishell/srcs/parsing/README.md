# 🧠 Parsing Module

> **Transforms user input into structured commands for execution.**
>
Handles tokenization, environment variable expansion, AST construction, and wildcard matching.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Subsystem](https://img.shields.io/badge/Subsystem-Parsing-blue?style=for-the-badge)

---

## 📖 Overview

The parsing module is responsible for breaking down user input, expanding variables, building the AST, and matching wildcards. It ensures commands are correctly structured for execution.

---
## 📂 Layout
- `ast/` — AST builder and manipulation
- `env/` — environment variable expansion and splitting
- `tokenizer/` — tokenization and syntax checking
- `wildcard/` — wildcard expansion and matching

---

## 🏗️ AST Submodule
Builds and manages the Abstract Syntax Tree (AST) for shell commands, pipelines, redirections, and subshells.

**Key files:**
- `builder.c` — builds AST from token lists, node creation/linking
- `cmd.c` — parses command nodes, arguments, options
- `redirections.c` — attaches redirection nodes
- `subshell.c` — builds subshell nodes (parentheses)
- `utils.c` — AST helpers, traversal, cleanup

**Flow:**
1. Token list → builder functions
2. AST nodes created for commands, pipelines, redirections, subshells
3. AST validated and returned for execution

---
## 🌱 Env Submodule
Handles environment variable expansion and splitting in command lines.

**Key files:**
- `expand/` — expands variables (e.g., `$HOME`, `$PATH`), handles quoting/edge cases
- `split/` — splits expanded variables into arguments

**Flow:**
1. Token scanned for variable patterns
2. Expansion replaces variables with environment values
3. Split breaks expanded values into arguments

---
## 🪄 Tokenizer Submodule
Tokenizes user input, checks syntax, and prepares tokens for parsing.

**Key files:**
- `utils.c` — token manipulation/classification
- `syntax/` — syntax checking (balanced quotes, valid operators)
- `tokenizer/` — main tokenization logic (splits input, handles quotes/escapes)

**Flow:**
1. Input → tokenizer
2. Tokenizer splits input, respects quotes/escapes
3. Syntax checker validates sequence
4. Tokens → AST builder

---
## 🦄 Wildcard Submodule
Expands wildcards in command arguments to match filesystem entries.

**Key files:**
- `expand.c` — scans tokens, expands wildcards to filenames
- `sort.c` — sorts matches per shell rules
- `match/` — pattern matching (glob logic)

**Flow:**
1. Token scanned for wildcards
2. Expansion finds matching files
3. Matches sorted and inserted into argument list

---
## 🛠️ Developer Notes
- Submodules are modular and testable
- Tokenization and syntax checking are strict to prevent parsing errors
- AST construction robustly handles pipelines, subshells, redirections
- Environment and wildcard expansion are integrated for seamless parsing

For detailed function documentation, see the source files and header definitions in `includes/parsing.h` and submodule headers.
# Parsing Module

This module is responsible for transforming user input into structured data that the shell can execute. It covers tokenization, environment variable expansion, AST (Abstract Syntax Tree) construction, and wildcard expansion.

## Directory Structure
- `ast/`: Builds and manipulates the Abstract Syntax Tree for command execution.
- `env/`: Handles environment variable expansion and splitting within command lines.
- `tokenizer/`: Tokenizes input strings, checks syntax, and prepares tokens for parsing.
- `wildcard/`: Expands wildcards (e.g., `*`, `?`) in command arguments.

---

## ast/
### Purpose
Constructs and manages the Abstract Syntax Tree (AST) representing shell commands, pipelines, redirections, and subshells.

### Key Files & Functions
- `builder.c`: Functions to build the AST from token lists. Handles node creation, linking, and error checking.
- `cmd.c`: Parses command nodes, arguments, and options. Converts tokens into command structures.
- `redirections.c`: Parses and attaches redirection nodes to commands. Handles input/output redirection syntax.
- `subshell.c`: Detects and builds subshell nodes (parentheses). Manages nested command execution.
- `utils.c`: Helper functions for AST manipulation, traversal, and cleanup.

### Typical Flow
1. Token list is passed to builder functions.
2. AST nodes are created for commands, pipelines, redirections, and subshells.
3. AST is validated and returned for execution.

---

## env/
### Purpose
Manages environment variable expansion and splitting within command lines.

### Key Files & Functions
- `expand/`: Functions to expand variables (e.g., `$HOME`, `$PATH`) in tokens. Handles quoting and edge cases.
- `split/`: Splits expanded variables into multiple arguments if needed (e.g., when expansion results in whitespace-separated values).

### Typical Flow
1. Token is scanned for variable patterns.
2. Expansion functions replace variables with their values from the environment.
3. Split functions break expanded values into arguments as required.

---

## tokenizer/
### Purpose
Tokenizes user input, checks syntax, and prepares tokens for parsing.

### Key Files & Functions
- `utils.c`: Utility functions for token manipulation and classification.
- `syntax/`: Syntax checking functions. Validates token sequences for correctness (e.g., balanced quotes, valid operators).
- `tokenizer/`: Main tokenization logic. Splits input into tokens, handles quoting, escapes, and operators.

### Typical Flow
1. Input string is passed to tokenizer.
2. Tokenizer splits input into tokens, respecting quotes and escapes.
3. Syntax checker validates token sequence.
4. Tokens are passed to AST builder.

---

## wildcard/
### Purpose
Expands wildcards in command arguments to match filesystem entries.

### Key Files & Functions
- `expand.c`: Main wildcard expansion logic. Scans tokens for wildcards and replaces them with matching filenames.
- `sort.c`: Sorts expanded matches according to shell rules.
- `match/`: Functions to match patterns against filenames (e.g., glob matching).

### Typical Flow
1. Token is scanned for wildcard patterns.
2. Expansion functions find matching files in the current directory.
3. Matches are sorted and inserted into the argument list.

---

## Developer Notes
- Each submodule is designed for modularity and testability.
- Tokenization and syntax checking are strict to prevent parsing errors.
- AST construction is robust, handling complex shell syntax (pipelines, subshells, redirections).
- Environment and wildcard expansion are integrated into parsing for seamless command execution.

For detailed function documentation, see the source files and header definitions in `includes/parsing.h` and submodule headers.
