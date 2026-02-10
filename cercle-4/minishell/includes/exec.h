/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:25:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/09 04:12:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// PACKAGE
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pwd.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <unistd.h>

// CUSTOM
# include "state.h"
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
	t_shell_state	*state;
	int				fd;
}			t_heredoc;

/* Public API used by other translation units */
void		print_sorted_env(char **envp);
int			process_export_arg(char *arg, t_shell_state *state);
int			process_existing_export(t_export_ctx *ctx, char ***envp);
int			process_new_export(t_export_ctx *ctx, char ***envp);
void		update_existing_env(char **envp, t_export_ctx *ctx);
void		parse_export_arg(char *arg, t_export_ctx *ctx);
int			report_invalid_identifier(char *arg, t_export_ctx *ctx);

int			exec_tree(t_ast *ast_node, t_shell_state *state);
int			exec_simple_command(t_ast *node, t_shell_state *state);
int			exec_subshell(t_ast *node, t_shell_state *state);
int			exec_logical_or(t_ast *node, t_shell_state *state);
int			exec_logical_and(t_ast *node, t_shell_state *state);
int			exec_redirection(t_ast *node, t_shell_state *state);
int			exec_pipe(t_ast *node, t_shell_state *state);
int			is_builtin(char *cmd, char **args, int is_quoted);
int			exec_builtin(char **args, t_shell_state *state);
int			scan_heredocs(t_ast *ast_node, t_shell_state *state);
void		consume_heredocs(t_nodes *tokens, t_shell_state *state);
int			ft_export(char **args, t_shell_state *state);
int			ft_unset(char **args, t_shell_state *state);
int			ft_env(t_shell_state *state);
int			ft_echo(char **args);

int			ft_pwd(t_shell_state *state);
int			ft_exit(char **args, t_shell_state *state);
int			ft_set_env(char *key, char *value, t_shell_state *state);
char		*find_path(char *cmd, t_shell_state *state);
int			get_env_index(char *key, t_shell_state *state);
int			is_valid_ident(char *str);
int			is_quoted_delim(const char *delim);
char		*remove_quotes_heredoc(char *str);
char		*generate_tmp_filename(int *fd_out);
char		*handle_heredoc_input(char **args, t_shell_state *state);
void		read_heredoc_loop(char *delim, int fd, t_shell_state *state);
char		*prepare_stop_str(char *delim, t_heredoc *ctx);
char		*heredoc_read_line(void);
char		*heredoc_read_line_non_tty(void);
int			process_line_quoted(char *line, char *stop_str, int fd);
int			process_line_unquoted(char *line, char *stop_str, int fd,
				t_heredoc *ctx);
void		read_heredoc_lines(char *stop_str, int quoted, t_heredoc *ctx);

int			ft_cd(char **args, t_shell_state *state);
char		*get_cd_path(char **args, t_shell_state *state);
char		*get_env_val_simple(char *key, t_shell_state *state);
char		*get_cwd_dup(void);
char		*resolve_home(t_shell_state *state);
char		*cdpath_find(const char *name, char *cdpath);
char		*join_paths(const char *a, const char *b);
int			perform_cd(char *path, t_shell_state *state);

char		*build_base_path(const char *path, t_shell_state *state,
				int *leading_slashes);
char		**collect_components(const char *base, int *count);
char		*build_path_from_stack(char **stack, int count,
				int leading_slashes);
char		*normalize_logical(const char *path, t_shell_state *state);
#endif
