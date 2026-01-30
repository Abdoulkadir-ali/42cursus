/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:14:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 14:01:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static char	*get_multiline_prompt(char code, t_op_def *ops)
{
	t_op_def	*def;
	char		prompt_buf[32];

	def = ext_get_op_def(ops, code);
	ft_bzero(prompt_buf, sizeof(prompt_buf));
	if (def && def->label)
	{
		ft_strlcpy(prompt_buf, def->label, sizeof(prompt_buf));
		ft_strlcat(prompt_buf, "> ", sizeof(prompt_buf));
		return (ft_strdup(prompt_buf));
	}
	else
		return (get_prompt(0));
}

static char	*read_and_append_line(t_line_struct *ls, t_op_def *ops,
		t_shell_state *state)
{
	char		*new_line;
	char		*temp;
	t_op_def	*def;

	new_line = read_input(ls->prompt, state);
	if (!new_line)
	{
		def = ext_get_op_def(ops, ls->code);
		if (def && def->counterpart)
			ft_puterror("unexpected EOF while looking for matching `%c'\n",
				def->counterpart);
		else
			ft_puterror("syntax error: unexpected end of file\n");
		state->syntax_error = 1;
		free(ls->line);
		return (NULL);
	}
	temp = append_line(ls->line, new_line);
	free(ls->line);
	free(new_line);
	return (temp);
}

static char	*read_next_line_and_append(t_line_struct *ls, t_op_def *ops,
		t_shell_state *state)
{
	char	*result;

	ls->prompt = get_multiline_prompt(ls->code, ops);
	result = read_and_append_line(ls, ops, state);
	free(ls->prompt);
	return (result);
}

char	*handle_multiline_input(char *line, t_shell_state *state)
{
	char			code;
	t_op_def		*ops;
	t_line_struct	ls;

	ops = get_ops();
	while (1)
	{
		code = ext_analyze_input(line);
		if (code == 0)
			break ;
		ls.line = line;
		ls.code = code;
		line = read_next_line_and_append(&ls, ops, state);
		if (!line)
			return (NULL);
	}
	return (line);
}
