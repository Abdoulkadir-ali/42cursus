/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:25:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 23:47:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

// PACKAGE
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// CUSTOM
# include "exec.h"
# include "libft.h"
# include "parsing.h"

# define SIGNAL_INTERACTIVE 1
# define SIGNAL_BLOCKING 2
# define SIGNAL_HEREDOC 3

typedef struct s_global_state
{
	char				**envp;
	int					exit_code;
	int					interactive_shell;
	int					expansion_error;
	int					last_signal;
}						t_global_state;

extern t_global_state	g_state;

/* backward-compatible alias for existing code */
# define g_last_signal (g_state.last_signal)
/* legacy global aliases -> map to fields in g_state */
# define g_envp (g_state.envp)
# define g_exit_code (g_state.exit_code)
# define g_interactive_shell (g_state.interactive_shell)
# define g_expansion_error (g_state.expansion_error)

// Function prototypes
void					print_ast(t_nodes *ast_node, int depth);
char					**duplicate_env(char **envp);
int						is_whitespace_only(char *str);
void					process_input(char *line, char ***envp, int *exit_code);
int						debug_dump_tokens_and_consume(t_nodes **ptokens);
int						check_syntax_and_consume(t_nodes *tokens,
							int *exit_code);
t_nodes					*extract_segment(t_nodes *cursor, t_nodes **pnext);
void					debug_dump_segment(t_nodes *segment);
int						try_handle_assignment_local(t_nodes *segment,
							char ***envp, int *exit_code);
int						try_handle_assignment_public(t_nodes *segment,
							char ***envp, int *exit_code);
char					*get_command_line(void);
void					setup_signals(int mode);
int						debug_dump_tokens_and_consume(t_nodes **ptokens);
void					debug_dump_segment(t_nodes *segment);
void					initialize_segment_builder(t_nodes **segment,
							t_nodes **seg_tail, t_nodes **it, t_nodes *cursor);
void					build_segment_until_semicolon(t_nodes **segment,
							t_nodes **seg_tail, t_nodes **it);
void					consume_semicolon_if_present(t_nodes *it,
							t_nodes **pneset_assignmentt);
int						check_if_assignment_candidate(t_nodes *segment,
							t_token **first_tok, char **eq);
int						validate_identifier(char *k);
void					perform_assignment(t_token *first_tok, char *eq,
							char ***envp, int *exit_code);
int						expand_and_check_error(t_nodes **segment, char **envp,
							int exit_code, int *new_exit_code);
void					execute_ast(t_nodes *segment, char ***envp,
							int *exit_code);
char					check_unclosed_quote(char *str);
char					*append_line(char *line, char *new_line);
char					*read_input(char *prompt);
char					*get_prompt(int is_initial);

#endif
