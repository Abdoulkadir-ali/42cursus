minishell/
├── includes/
│   ├── minishell.h       # Global defines, structures, and includes
│   ├── parser.h          # AST and Token structures
│   └── executor.h        # Execution logic prototypes
├── src/
│   ├── main.c            # The REPL loop (readline, add_history)
│   ├── signals.c         # Signal handlers (Ctrl+C, Ctrl+Z)
│   ├── parsing/
│   │   ├── tokenizer.c   # String to Tokens
│   │   ├── env_expand.c  # $VAR expansion
│   │   └── ast_builder.c # Tokens to AST
|   ├── executor/
│   │   ├── exec_tree.c   # AST traversal logic
│   │   ├── path_finder.c # PATH searching (access, stat)
│   │   └── pipe_utils.c  # dup2 and pipe logic
│   └── utils/
│       ├── memory.c      # Tree/Array freeing functions
│       └── error.c       # Custom perror wrappers
├── libft/                # Your custom library (if used)
└── Makefile              # Rules to compile the project

1. The Data Flow (Pipeline)

A clean architecture follows this linear path. Each step "hands off" a specific data type to the next.
A. Lexer (Scanner)

    Input: char * (Raw string from readline).

    Action: Breaks string into a Linked List of Tokens.

    Logic: Handles state (inside vs. outside quotes).

    Output: t_token * list.

B. Parser

    Input: t_token * list.

    Action: Validates syntax (e.g., checks for | |) and builds the AST.

    Logic: Identifies "highest priority" operators (Pipes) and makes them the root nodes.

    Output: t_ast *root.

C. Expansion (Often inside Parser)

    Action: Before sending to execution, replace $USER with environment values and remove the literal quotes ("ls" becomes ls).

D. Executor

    Input: t_ast *node.

    Action: Recursive traversal.

    Logic: If NODE_PIPE, call pipe(). If NODE_CMD, call fork() and execve().

3. Key Data Structures (includes/parser.h)

Defining your structures correctly is 50% of the work.
C

typedef enum e_token_type {
    TOKEN_WORD,    // ls, -l
    TOKEN_PIPE,    // |
    TOKEN_RED_IN,  // <
    TOKEN_RED_OUT  // >
} t_token_type;

typedef struct s_token {
    char            *value;
    t_token_type     type;
    struct s_token  *next;
} t_token;

typedef struct s_ast {
    t_token_type    type;      // PIPE or WORD
    char            **args;    // NULL unless type is WORD
    struct s_ast    *left;     // Left side of pipe
    struct s_ast    *right;    // Right side of pipe
} t_ast;

4. Why this structure?

    Debugging: If the command ls | grep fails, you can print the Token list to see if the Lexer is broken, or the AST to see if the Parser is broken.

    Memory Management: You can write a single function free_ast(t_ast *node) that recursively cleans up the entire command tree.

    Teamwork: One person can work on the lexer/ while another works on executor/ without touching the same files.