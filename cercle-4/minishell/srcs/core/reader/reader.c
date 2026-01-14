/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 03:30:41 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/14 17:47:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static char	*read_input(char *prompt)
{
	char	*buf;
	int		i;
	char	c;

	if (isatty(STDIN_FILENO))
		return (readline(prompt));
	buf = ft_calloc(10000, 1);
	i = 0;
	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		buf[i++] = c;
		if (c == '\n')
			break ;
		if (i >= 9999)
			break ;
	}
	if (i > 0)
	{
		if (buf[i - 1] == '\n')
			buf[i - 1] = '\0';
		return (buf);
	}
	free(buf);
	return (NULL);
}

static char	*read_next_line_and_append(char *line, char quote)
{
	char	*prompt;
	char	*new_line;
	char	*temp;

	prompt = get_prompt(0);
	new_line = read_input(prompt);
	if (!new_line)
	{
		ft_puterror("unexpected EOF while looking for matching `%c'\n",
			quote);
		free(line);
		return (NULL);
	}
	temp = append_line(line, new_line);
	free(line);
	free(new_line);
	return (temp);
}
static char	check_unclosed_quote(char *str)
{
	char	quote;

	quote = 0;
	while (*str)
	{
		if (quote == 0)
		{
			if (*str == '\'' || *str == '"')
				quote = *str;
		}
		else
		{
			if (*str == quote)
				quote = 0;
		}
		str++;
	}
	return (quote);
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
