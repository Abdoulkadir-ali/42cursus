/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:24:46 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/19 05:20:39 by abdoali          ###   ########.fr       */
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
# include "parsing.h"
# include "state.h"

# define CD_MAX_COMPONENTS 1024
# define DEFAULT_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

typedef struct s_export
{
	char			*key;
	char			*new_entry;
	char			*eq;
	bool			append;
	size_t			idx;
}					t_export;

typedef struct s_quotes_state
{
	size_t			i;
	size_t			j;
	char			quote;
}					t_quotes_state;

typedef struct s_heredoc
{
	t_shell_state	*state;
	int				fd;
}					t_heredoc;

typedef struct s_builtin_def
{
	const char		*name;
	int				(*func)(char **, t_shell_state *);
}					t_builtin_def;

/* Public API used by other translation units */
void				print_sorted_env(char **envp);
int					process_export_arg(char *arg, t_shell_state *state);
int					process_existing_export(t_export *exp, char ***envp);
int					process_new_export(t_export *exp, char ***envp);
void				update_existing_env(char **envp, t_export *exp);
void				parse_export_arg(char *arg, t_export *exp);
int					report_invalid_identifier(char *arg, t_export *exp);

int					exec_tree(t_ast *ast_node, t_shell_state *state);
int					exec_simple_command(t_ast *node, t_shell_state *state);
char				**expand_string_array(char **arr, t_shell_state *state);
char				**expand_redirection_filename(char *filename,
						t_shell_state *state);
void				free_string_array(char **arr);
int					exec_subshell(t_ast *node, t_shell_state *state);
int					exec_task(t_ast *node, t_shell_state *state);
int					exec_logical(t_ast *node, t_shell_state *state,
						bool run_if_zero);
/* Internal helpers used across exec submodules */
int					exec_builtin_with_assigns(t_ast *node,
						t_shell_state *state);
int					exec_external_with_lookup(t_ast *node,
						t_shell_state *state);
void				apply_assigns_to_state(t_ast *node, t_shell_state *state);
int					save_and_apply_assigns(t_ast *node, t_shell_state *state,
						char ***saved_env);
void				restore_env_and_free(t_shell_state *state,
						char **saved_env);
/* internal helpers in exec/assignment.c are file-local; do not export */
/* Error helpers implemented in srcs/exec/ast/error.c */
int					report_command_not_found(char *cmd, t_shell_state *state);
int					report_fork_error(void);
void				report_quit_core_dump(void);

/* Expansion helpers relocated to srcs/exec/ast/expand.c */
char				**expand_string_array(char **arr, t_shell_state *state);
char				**expand_redirection_filename(char *filename,
						t_shell_state *state);
void				free_string_array(char **arr);
int					exec_redirection(t_ast *node, t_shell_state *state);
int					open_redirection_file(t_ast *node, int *fd);
int					get_target_fd(t_ast *node);
int					setup_redirection(int target_fd, int fd, int *save_fd);
int					exec_pipe(t_ast *node, t_shell_state *state);
bool				is_builtin(char *cmd, char **args);
const t_builtin_def	*get_builtins(void);
int					exec_builtin(char **args, t_shell_state *state);
int					scan_heredocs(t_ast *ast_node, t_shell_state *state);
int					handle_wait_status(int status);
void				consume_heredocs(t_nodes *tokens, t_shell_state *state);
int					ft_export(char **args, t_shell_state *state);
int					ft_unset(char **args, t_shell_state *state);
int					ft_env(char **args, t_shell_state *state);
int					ft_echo(char **args, t_shell_state *state);
int					ft_pwd(char **args, t_shell_state *state);
int					ft_exit(char **args, t_shell_state *state);
int					ft_set_env(char *key, char *value, t_shell_state *state);
char				*find_path(char *cmd, t_shell_state *state);
size_t				count_env(char **envp);
bool				is_valid_ident(char *str);
bool				is_quoted_delim(const char *delim);
char				*remove_quotes_heredoc(char *str);
char				*generate_tmp_filename(int *fd_out);
char				*handle_heredoc_input(char **args, t_shell_state *state);
char				*expand_delim(const char *delim, t_shell_state *state);
void				read_heredoc_loop(char *delim, int fd, t_shell_state *state,
						bool is_quoted);
char				*heredoc_read_line(void);
char				*heredoc_read_line_non_tty(void);
int					process_line_quoted(char *line, char *stop_str, int fd);
int					process_line_unquoted(char *line, char *stop_str, int fd,
						t_heredoc *heredoc);
void				read_heredoc_lines(char *stop_str, bool quoted,
						t_heredoc *heredoc);

int					ft_cd(char **args, t_shell_state *state);
char				*get_cd_path(char **args, t_shell_state *state);
char				*get_cwd_dup(void);
char				*resolve_home(t_shell_state *state);
char				*cdpath_find(const char *name, char *cdpath);
char				*join_paths(const char *a, const char *b);
int					perform_cd(char *path, t_shell_state *state);
void				report_command_not_found_old(void);
pid_t				fork_protected(void);
int					pipe_protected(int pipefd[2]);

char				*build_base_path(const char *path, t_shell_state *state,
						size_t *leading_slashes);
char				**collect_components(const char *base, size_t *count);
char				*build_path_from_stack(char **stack, size_t count,
						size_t leading_slashes);
char				*normalize_logical(const char *path, t_shell_state *state);
void				init_builtin_entry(t_builtin_def *entry, const char *name,
						int (*func)(char **, t_shell_state *));
void				init_builtins(t_builtin_def *builtins);

#endif
