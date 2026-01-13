/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 03:30:41 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 01:25:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

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

static char	*append_line(char *line, char *new_line)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(line, "\n");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, new_line);
	free(temp);
	return (result);
}

static char	*read_input(char *prompt)
{
	char	*line;
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
		line = buf;
	}
	else
	{
		free(buf);
		line = NULL;
	}
	return (line);
}

char	*get_command_line(void)
{
	char	*line;
	char	*new_line;
	char	*temp;
	char	quote;
	char	*prompt;

	prompt = "minishell> ";
	if (!isatty(STDIN_FILENO))
		prompt = NULL;
	line = read_input(prompt);
	if (!line)
		return (NULL);
	while ((quote = check_unclosed_quote(line)) != 0)
	{
		prompt = "> ";
		if (!isatty(STDIN_FILENO))
			prompt = NULL;
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
		if (!temp)
			return (NULL);
		line = temp;
	}
	return (line);
}
