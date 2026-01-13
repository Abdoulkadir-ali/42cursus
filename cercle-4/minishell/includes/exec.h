/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:25:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 03:25:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXEC_H
# define EXEC_H

// PACKAGE
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

// CUSTOM
# include "core.h"
# include "parsing.h"

int		exec_tree(t_nodes *ast_node, char ***envp);
int		exec_simple_command(t_ast *node, char ***envp);
int		exec_pipe(t_ast *node, char ***envp);
int		is_builtin(char *cmd, char **args);
int		exec_builtin(char **args, char ***envp);
int		scan_heredocs(t_nodes *ast_node);
void	consume_heredocs(t_nodes *tokens);
int		ft_export(char **args, char ***envp);
int		ft_unset(char **args, char ***envp);
int		ft_env(char **envp);
int		ft_echo(char **args);
int		ft_cd(char **args, char ***envp);
int		ft_pwd(void);
int		ft_exit(char **args);
int		ft_set_env(char *key, char *value, char ***envp);
char	*find_path(char *cmd, char **envp);
int		get_env_index(char *key, char **envp);
int		is_valid_ident(char *str);
int		is_quoted_delim(const char *delim);
char	*remove_quotes_heredoc(char *str);
char	*generate_tmp_filename(void);
char	*handle_heredoc_input(char *delim, char **envp, int exit_code);
void	read_heredoc_loop(char *delim, int fd, char **envp, int exit_code);

/* legacy globals removed; use g_state aliases in core.h */

#endif
