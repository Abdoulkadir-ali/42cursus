/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:16:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 14:05:51 by abdoali          ###   ########.fr       */
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
# include "state.h"
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

typedef struct s_line_struct
{
	char	*line;
	char	*prompt;
	char	code;
}			t_line_struct;

// Function prototypes
int			is_whitespace_only(char *str);
void		process_input(char *line, t_shell_state *state);

int			try_handle_assignment_public(t_nodes *segment,
				t_shell_state *state);
char		*get_command_line(t_shell_state *state);
void		setup_signals(int mode);
void		initialize_segment_builder(t_nodes **segment, t_nodes **seg_tail,
				t_nodes **it, t_nodes *cursor);
void		build_segment_until_semicolon(t_nodes **segment, t_nodes **seg_tail,
				t_nodes **it);
void		consume_semicolon_if_present(t_nodes *it,
				t_nodes **pneset_assignmentt);
int			check_if_assignment_candidate(t_nodes *segment, t_token **first_tok,
				char **eq);
int			expand_and_check_error(t_nodes **segment, t_shell_state *state,
				int *new_exit_code);
void		execute_ast(t_nodes *segment, t_shell_state *state);

/* Utils */
char		*append_line(char *line, char *new_line);
char		*get_prompt(int is_initial);
char		*read_input(char *prompt, t_shell_state *state);
char		*handle_parenthesis(char *line, char *trimmed,
				t_shell_state *state);
char		*handle_multiline_input(char *line, t_shell_state *state);
char		*read_function_body(char *line, size_t n, t_shell_state *state);

/* Extender (srcs/core/reader/extender.c) */
t_op_def	*get_ops(void);
t_op_def	*ext_get_op_def(t_op_def *ops, char code);
char		ext_analyze_input(char *line);

#endif