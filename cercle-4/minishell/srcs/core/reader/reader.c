/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 03:30:41 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 22:54:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static char	*read_next_line_and_append(char *line, char quote)
{
	char	*prompt;
	char	*new_line;
	char	*temp;

	prompt = get_prompt(0);
	new_line = read_input(prompt);
	if (!new_line)
	{
		ft_printf_fd(2,
			"minishell: unexpected EOF while looking for matching `%c'\n",
			quote);
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
	char	quote;

	quote = check_unclosed_quote(line);
	while (quote)
	{
		line = read_next_line_and_append(line, quote);
		if (!line)
			return (NULL);
		quote = check_unclosed_quote(line);
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
