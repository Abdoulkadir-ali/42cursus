_This project has been created as part of the 42 curriculum by abdoali, hbranco._

# minishell

## Description

minishell is a compact Unix-like interactive command-line shell implemented for the 42 curriculum. It reimplements a practical subset of standard shell behavior — tokenization and AST-based parsing, word and variable expansion (including quotes and environment variables), wildcard expansion, command execution via `execve`, pipelines, redirections and heredoc handling, builtin commands, and basic signal handling — all while respecting the project's constraints and expected behaviour for correctness and portability.

## Instructions

From the repository root: build the project with `make` (this compiles the sources and links the included `libft`), then run the shell from the root directory with `./minishell`. Exit the shell with `exit` or Ctrl-D.

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
- POSIX Shell specification and related documentation — primary reference for expected shell behaviour
- GNU readline manual — reference for interactive line editing (if used)
- Man pages: `execve(2)`, `fork(2)`, `pipe(2)`, `dup2(2)`, `waitpid(2)`, `signal(7)`

AI usage disclosure:

AI was used only for modest, non-functional assistance: suggesting phrasing for the README and docblocks, improving comment wording, and making small stylistic edits to documentation text. Specifically, AI helped with phrasing and wording in README content and comments; it was not used to write production code, implement parsing/expansion/execution logic, design algorithms, or create tests. All functional code, design choices, and reviews were performed by the project authors (abdoali, hbranco).