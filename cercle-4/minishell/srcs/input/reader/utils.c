/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:15:13 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 05:09:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static char	*append_with_backslash(char *line, char *new_line, int i)
{
	char	*result;

	line[i] = '\0';
	result = ft_strjoin(line, new_line);
	return (result);
}

static char	*append_with_newline(char *line, char *new_line)
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

char	*append_line(char *line, char *new_line)
{
	int		len;
	int		i;

	if (!line || !new_line)
		return (NULL);
	len = ft_strlen(line);
	i = len - 1;
	while (i >= 0 && ft_isspace(line[i]))
		i--;
	if (i >= 0 && line[i] == '\\')
		return (append_with_backslash(line, new_line, i));
	else
		return (append_with_newline(line, new_line));
}

char	*get_prompt(int is_initial)
{
	if (!isatty(STDIN_FILENO))
		return (NULL);
	if (is_initial)
		return ("minishell> ");
	return ("> ");
}

char	*read_input(char *prompt)
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
