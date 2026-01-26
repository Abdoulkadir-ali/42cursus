/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:25:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 04:13:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// PACKAGE
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pwd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

// CUSTOM
# include "core.h"
# include "parsing.h"

typedef struct s_export_ctx
{
	char	*key;
	char	*new_entry;
	char	*eq;
	int		append;
	int		idx;
}			t_export_ctx;

typedef struct s_quotes_state
{
	int		i;
	int		j;
	char	quote;
}			t_quotes_state;

typedef struct s_heredoc
{
	char	**envp;
	int		exit_code;
	int		fd;
}			t_heredoc;

/* Public API used by other translation units */
void		print_sorted_env(char **envp);
int			process_export_arg(char *arg, char ***envp);
void		parse_export_arg(char *arg, t_export_ctx *ctx);
int			report_invalid_identifier(char *arg, t_export_ctx *ctx);

int			exec_tree(t_nodes *ast_node, char ***envp);
int			exec_simple_command(t_ast *node, char ***envp);
int			exec_subshell(t_ast *node, char ***envp);
int			exec_logical_or(t_ast *node, char ***envp);
int			exec_logical_and(t_ast *node, char ***envp);
int			exec_redirection(t_ast *node, char ***envp);
int			exec_pipe(t_ast *node, char ***envp);
int			is_builtin(char *cmd, char **args, int is_quoted);
int			exec_builtin(char **args, char ***envp);
int			scan_heredocs(t_nodes *ast_node);
void		consume_heredocs(t_nodes *tokens);
int			ft_export(char **args, char ***envp);
int			ft_unset(char **args, char ***envp);
int			ft_env(char **envp);
int			ft_echo(char **args);

int			ft_pwd(char **envp);
int			ft_exit(char **args);
int			ft_set_env(char *key, char *value, char ***envp);
char		*find_path(char *cmd, char **envp);
int			get_env_index(char *key, char **envp);
int			is_valid_ident(char *str);
int			is_quoted_delim(const char *delim);
char		*remove_quotes_heredoc(char *str);
char		*generate_tmp_filename(void);
char		*handle_heredoc_input(char *delim, char **envp, int exit_code);
void		read_heredoc_loop(char *delim, int fd, char **envp, int exit_code);
char		*prepare_stop_str(char *delim, t_heredoc *ctx);
char		*read_line(void);
int			process_line_quoted(char *line, char *stop_str, int fd);
int			process_line_unquoted(char *line, char *stop_str, int fd,
				t_heredoc *ctx);
void		read_heredoc_lines(char *stop_str, int quoted, t_heredoc *ctx);

int			ft_cd(char **args, char ***envp);
char		*get_cd_path(char **args, char **envp);
char		*get_env_val_simple(char *key, char **envp);
char		*get_cwd_dup(void);
char		*resolve_home(char **envp);
char		*cdpath_find(const char *name, char *cdpath);
char		*join_paths(const char *a, const char *b);

char		*build_base_path(const char *path, char **envp,
				int *leading_slashes);
char		**collect_components(const char *base, int *count);
char		*build_path_from_stack(char **stack, int count,
				int leading_slashes);
char		*normalize_logical(const char *path, char **envp);
#endif
