/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:14:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/21 07:25:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static char	*read_next_line_and_append(char *line, char code, const t_op_def *ops)
{
	char			*prompt;
	char			*new_line;
	char			*temp;
	const t_op_def	*def;
	char			prompt_buf[32];

	def = ext_get_op_def(ops, code);
	if (def && def->label)
	{
		ft_bzero(prompt_buf, sizeof(prompt_buf));
		ft_strlcpy(prompt_buf, def->label, sizeof(prompt_buf));
		ft_strlcat(prompt_buf, "> ", sizeof(prompt_buf));
		prompt = prompt_buf;
	}
	else
		prompt = get_prompt(0);
	new_line = read_input(prompt);
	if (!new_line)
	{
		if (def && def->counterpart)
			ft_puterror("unexpected EOF while looking for matching `%c'\n",
				def->counterpart);
		else
			ft_puterror("syntax error: unexpected end of file\n");
		free(line);
		return (NULL);
	}
	temp = append_line(line, new_line);
	free(line);
	free(new_line);
	return (temp);
}

static char	*handle_multiline_input(char *line)
{
	char			code;
	const t_op_def	*ops;

	ops = get_ops();
	while (1)
	{
		code = ext_analyze_input(line);
		if (code == 0)
			break ;
		line = read_next_line_and_append(line, code, ops);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*get_command_line(void)
{
	char	*line;
	char	*prompt;

	prompt = get_prompt(1);
	line = read_input(prompt);
	if (!line)
		return (NULL);
	return (handle_multiline_input(line));
}
