#ifndef EXEC_H
# define EXEC_H

# include "parsing.h"
# include "core.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

int		exec_tree(t_nodes *ast_node, char ***envp);
int		exec_simple_command(t_ast *node, char ***envp);
int		exec_pipe(t_ast *node, char ***envp);

int		is_builtin(char *cmd, char **args);
int		exec_builtin(char **args, char ***envp);

int		scan_heredocs(t_nodes *ast_node);

int		ft_export(char **args, char ***envp);
int		ft_unset(char **args, char ***envp);
int		ft_env(char **envp);

char	*find_path(char *cmd, char **envp);

#endif
