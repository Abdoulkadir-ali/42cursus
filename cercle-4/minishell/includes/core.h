#ifndef CORE_H
# define CORE_H

# include "libft.h"
# include "parsing.h"
# include "exec.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SIGNAL_INTERACTIVE 1
# define SIGNAL_BLOCKING 2
# define SIGNAL_HEREDOC 3

extern int	g_last_signal;

// Function prototypes
void print_ast(t_nodes *ast_node, int depth);
char **duplicate_env(char **envp);
void execute_command(t_nodes *tokens, char ***envp, int *exit_code);
int is_whitespace_only(char *str);
void process_input(char *line, char ***envp, int *exit_code);
char	*get_command_line(void);
void	setup_signals(int mode);

#endif
