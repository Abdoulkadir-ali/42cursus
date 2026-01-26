/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:16:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/25 23:48:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

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

typedef struct s_op_def
{
	char	code;
	char	*symbol;
	char	*label;
	char	counterpart;
}			t_op_def;

// Function prototypes
int			is_whitespace_only(char *str);
void		process_input(char *line, char ***envp, int *exit_code);

int			try_handle_assignment_public(t_nodes *segment, char ***envp,
				int *exit_code);
char		*get_command_line(void);
void		setup_signals(int mode);
void		initialize_segment_builder(t_nodes **segment, t_nodes **seg_tail,
				t_nodes **it, t_nodes *cursor);
void		build_segment_until_semicolon(t_nodes **segment, t_nodes **seg_tail,
				t_nodes **it);
void		consume_semicolon_if_present(t_nodes *it,
				t_nodes **pneset_assignmentt);
int			check_if_assignment_candidate(t_nodes *segment, t_token **first_tok,
				char **eq);
int			expand_and_check_error(t_nodes **segment, char **envp,
				int exit_code, int *new_exit_code);
void		execute_ast(t_nodes *segment, char ***envp, int *exit_code);

/* Utils */
char		*append_line(char *line, char *new_line);
char		*get_prompt(int is_initial);
char		*read_input(char *prompt);
char		*handle_parenthesis(char *line, char *trimmed);
char		*handle_multiline_input(char *line);

/* Extender (srcs/core/reader/extender.c) */
t_op_def	*get_ops(void);
t_op_def	*ext_get_op_def(t_op_def *ops, char code);
char		ext_analyze_input(char *line);

#endif