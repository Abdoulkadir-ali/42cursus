minishell/
├── includes/
│   ├── minishell.h       # Global defines, structures, and includes
│   ├── parser.h          # AST and Token structures
│   └── executor.h        # Execution logic prototypes
├── src/
│   ├── core/
│   │   ├── main.c        # The REPL loop (readline, add_history)
│   │   └── signals.c     # Signal handlers (Ctrl+C, Ctrl+Z, Ctrl+\)
│   ├── parsing/
│   │   ├── tokenizer.c   # String to Tokens (Lexer)
│   │   ├── env_expand.c  # $VAR expansion & Quote removal
│   │   └── ast_builder.c # Tokens to AST (Parser)
│   ├── executor/
│   │   ├── exec_tree.c   # AST traversal logic
│   │   ├── path_finder.c # PATH searching (access, stat)
│   │   ├── pipe.c        # Pipe logic (fork/dup2)
│   │   ├── builtins.c    # Builtin command routing
│   │   └── heredoc.c     # Heredoc handling (tmp file or pipe)
│   └── utils/
│       ├── memory.c      # Tree/Array freeing functions
│       └── error.c       # Custom perror wrappers
├── libft/                # Custom library
└── Makefile              # Compilation rules

## 0. Subject Constraints & Requirements
- **Global Variable**: Only ONE allowed. (Recommendation: `int g_signal;` to communicate signal reception to the main loop).
- **Quotes**: Handle `'` (no interpretation) and `"` (interpret `$`). No unclosed quotes.
- **Special Characters**: Do NOT interpret `\` or `;`.
- **Redirections**: `<`, `>`, `<<` (heredoc), `>>`.
    - **Heredoc**: Read until delimiter. Do NOT update history.
- **Pipes**: `|` connects stdout to stdin.
- **Environment**: Expand `$VAR` and `$?`.
- **Signals**: `Ctrl-C` (new line), `Ctrl-D` (exit), `Ctrl-\` (no-op in interactive).
    - *Note*: `readline` leaks are acceptable, but YOUR code must not leak.

## 1. The Data Flow (Pipeline)
A clean architecture follows this linear path. Each step "hands off" a specific data type to the next.

### A. Lexer (Scanner)
- **Input**: `char *line` (Raw string from readline).
- **Action**: Breaks string into a Linked List of Tokens.
- **Logic**: Handles state (inside vs. outside quotes).
    - `ls -l` -> `[TOKEN_WORD "ls"] -> [TOKEN_WORD "-l"]`
    - `ls|grep` -> `[TOKEN_WORD "ls"] -> [TOKEN_PIPE "|"] -> [TOKEN_WORD "grep"]`
- **Output**: `t_token *list`.

### B. Parser (AST Builder)
- **Input**: `t_token *list`.
- **Action**: Validates syntax (checks for double pipes `||`, open quotes) and builds the AST.
- **Logic**: Identifies "highest priority" operators (Pipes) and makes them the root nodes.
    - `ls | grep a` becomes:
      ```
          PIPE
         /    \
       ls    grep a
      ```
- **Output**: `t_ast *root`.

### C. Expansion (Pre-Execution)
- **Action**: Before execution (or during parsing), replace strings.
    1. **Environment Variables**: Replace `$USER` with value. Handle `$?` (exit status).
    2. **Quote Removal**: Remove outer quotes. `'hello'` -> `hello`.

### D. Executor
- **Input**: `t_ast *node`, `char ***envp`.
- **Action**: Recursive traversal.
- **Logic**:
    - **NODE_PIPE**:
        1. `pipe(fd)`.
        2. `fork()` Left Child -> `dup2(fd[1], STDOUT)`.
        3. `fork()` Right Child -> `dup2(fd[0], STDIN)`.
        4. Parent closes `fd[0]` and `fd[1]`, then `waitpid()` for both.
    - **NODE_CMD**:
        1. Check if Builtin -> Execute in parent (if no pipe) or child.
        2. If not builtin -> `fork()`, Find PATH, `execve()`.

## 2. Key Data Structures (includes/parser.h)

```c
typedef enum e_token_type {
    TOKEN_WORD,    // ls, -l
    TOKEN_PIPE,    // |
    TOKEN_RED_IN,  // <
    TOKEN_RED_OUT, // >
    TOKEN_HEREDOC, // <<
    TOKEN_APPEND   // >>
} t_token_type;

typedef struct s_token {
    char            *value;
    t_token_type     type;
    struct s_token  *next;
} t_token;

typedef struct s_ast {
    t_token_type    type;      // PIPE, WORD, REDIRECT
    char            **args;    // NULL unless type is WORD
    struct s_ast    *left;     // Left side of pipe/redirect
    struct s_ast    *right;    // Right side of pipe/command
} t_ast;
```

## 3. Critical Systems

### Signal Handling
- **Global Variable**: Use `extern int g_last_signal;` (or similar) to handle strict check instructions.
- **Interactive Mode**:
    - `SIGINT` (Ctrl+C): `write(1, "\n", 1); rl_on_new_line(); rl_replace_line("", 0); rl_redisplay();`
    - `SIGQUIT` (Ctrl+\): `SIG_IGN` (Ignore).
- **Blocking Mode (Child)**:
    - `SIGINT`: Default (terminate).
    - `SIGQUIT`: Default (core dump). Print `Quit (core dumped)\n` in parent if `WTERMSIG(status) == SIGQUIT`.
- **Heredoc**: `SIGINT` interrupts input loop.

### Builtins (Mandatory)
These must behave exactly as requested:
- `echo` (`-n` supported).
- `cd` (relative/absolute path only).
- `pwd` (no options).
- `export` (no options).
- `unset` (no options).
- `env` (no options/arguments).
- `exit` (no options - typically means don't handle flags, but argument usually allowed in bash).

### Heredocs (`<< DELIM`)
- **Parsing**: Read from stdin until `DELIM` line seen.
- **History**: Do **NOT** add heredoc lines to history.
- **Expansion**: Expand vars unless `DELIM` is quoted.

## 4. Bonus Part (Only if Mandatory Perfect)
- `&&` and `||` with parenthesis priorities.
- Wildcard `*` in current directory.