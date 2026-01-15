/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:25:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:49:52 by abdoali          ###   ########.fr       */
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

// The global variable poses a risk of racing condtion
extern t_global_state	g_state;
// However we're NOT allowed to use semaphores in the project.

// Function prototypes
int						is_whitespace_only(char *str);
void					process_input(char *line, char ***envp, int *exit_code);

int						try_handle_assignment_public(t_nodes *segment,
							char ***envp, int *exit_code);
char					*get_command_line(void);
void					setup_signals(int mode);
void					initialize_segment_builder(t_nodes **segment,
							t_nodes **seg_tail, t_nodes **it, t_nodes *cursor);
void					build_segment_until_semicolon(t_nodes **segment,
							t_nodes **seg_tail, t_nodes **it);
void					consume_semicolon_if_present(t_nodes *it,
							t_nodes **pneset_assignmentt);
int						check_if_assignment_candidate(t_nodes *segment,
							t_token **first_tok, char **eq);
int						expand_and_check_error(t_nodes **segment, char **envp,
							int exit_code, int *new_exit_code);
void					execute_ast(t_nodes *segment, char ***envp,
							int *exit_code);
char					*append_line(char *line, char *new_line);
char					*get_prompt(int is_initial);

#endif
