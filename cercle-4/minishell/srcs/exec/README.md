# Exec Module

Handles command execution, process management, builtins, environment manipulation, and heredoc support. This subsystem is responsible for running parsed commands, managing pipes and redirections, and integrating shell builtins.

---

## 📂 Directory Structure
- `srcs/exec/` — Execution layer root
  - `ast/` — AST-based execution: control flow, path resolution, pipes, redirections, and process waiting
  - `builtins/` — Builtin command drivers and glue to exec layer
  - `env/` — Environment helpers and builtin implementations
  - `heredoc/` — Heredoc generator, reader, and expansion

---

## 🏗️ How It Works

### `ast/`
- **control.c**: Implements execution control flow (e.g., sequential, conditional, pipeline execution).
- **path.c**: Resolves executable paths using environment variables and search logic.
- **pipe.c**: Sets up and manages pipes for command pipelines.
- **redirection.c**: Handles input/output redirection, file descriptor manipulation.
- **simple.c**: Executes simple commands (no pipeline/redirection).
- **tree.c**: Traverses and executes AST nodes recursively.
- **wait.c**: Waits for child processes, collects exit statuses.

#### Typical Flow
1. AST is traversed and executed node by node.
2. Pipes and redirections are set up as needed.
3. Commands are launched, builtins are handled, and processes are waited on.

---

### `builtins/`
- **exec.c**: Dispatches builtin commands, integrates with exec layer.
- **init.c**: Initializes builtin command context and registration.
- **functions/**: Implements individual builtin command logic (e.g., `cd`, `echo`, `pwd`, `env`, `export`, `unset`, `exit`).

#### Typical Flow
1. Builtin command is detected and dispatched.
2. Context is initialized and command logic is executed.
3. Result is returned to exec layer for further processing.

---

### `env/`
- **print.c**: Prints environment variables.
- **set.c**: Sets and updates environment variables.
- **utils.c**: Helper functions for environment manipulation.
- **process/**: Manages environment context for child processes.

#### Typical Flow
1. Environment is initialized and updated as needed.
2. Builtins interact with environment helpers for `export`, `unset`, etc.
3. Child processes inherit or modify environment context.

---

### `heredoc/`
- **consume.c**: Reads heredoc input from user, stores in temporary files.
- **expand.c**: Expands variables within heredoc input.
- **input.c**: Handles heredoc input stream setup.
- **quotes.c**: Manages quote handling in heredoc input.
- **read.c**: Reads heredoc content for command execution.
- **scan.c**: Scans heredoc delimiters and manages input flow.
- **utils.c**: Helper functions for heredoc management.

#### Typical Flow
1. Heredoc delimiter is detected in command line.
2. Input is read, expanded, and stored securely.
3. Heredoc content is provided to command as input during execution.

---

## 🛠️ Developer Notes
- AST-based execution enables robust handling of pipelines, redirections, and subshells.
- Builtins are modular and integrated with exec layer for seamless command handling.
- Environment helpers ensure consistent context across processes and builtins.
- Heredoc handling is secure and supports variable expansion and quote management.

For detailed function documentation, see the source files and header definitions in `includes/exec.h` and submodule headers.
