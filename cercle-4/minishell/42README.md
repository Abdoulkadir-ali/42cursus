_This project has been created as part of the 42 curriculum by abdoali, hbranco._

# minishell

## Description

minishell is a small Unix-like command-line shell implemented for the 42
curriculum. Its goal is to reimplement a subset of the standard shell
behaviour (parsing, expansion, redirections, pipelines, builtins, heredocs,
and signal handling) while respecting project constraints and expected
functionality.

## Features (brief)

- Tokenization and AST-based parsing
- Variable expansion and wildcard expansion
- Redirections and heredoc support
- Builtin commands (cd, echo, exit, env, export, unset, pwd)
- Pipeline execution and simple job control
- Signal handling integrated with the interactive prompt and heredoc

## Requirements

- POSIX-compatible OS (Linux / macOS)
- C compiler (gcc/clang)
- Make

## Build & Run

From the repository root:

```sh
make
./minishell
```

## Usage examples

```sh
# after building
./minishell
ls -la | grep src
export FOO=bar
echo $FOO
```

## Resources

- POSIX Shell specification and related documentation
- GNU readline manual
- Man pages: `execve(2)`, `fork(2)`, `pipe(2)`, `dup2(2)`, `waitpid(2)`, `signal(7)`

## AI usage disclosure

AI assistance was used for small non-functional tasks only, such as
suggesting concise docblocks and improving comment wording. All core code
logic and implementation decisions were made by the project authors.

## Technical choices

- Language: C (ISO C, POSIX APIs)
- Build: Makefile
- Minimal external dependencies (includes local libft)

## Contributors

- abdoali
- hbranco

## Where to find more information

See the source under `srcs/` and headers in `includes/` for implementation
details and data structures.

If you want more sections (design notes, tests, developer guide), tell me
which area to expand.

