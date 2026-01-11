/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 03:30:41 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 13:20:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_command_line(void)
{
	char	*line;
	char	*new_line;
	char	*temp;
	char	quote;

	line = readline("minishell> ");
	if (!line)
		return (NULL);
	while ((quote = check_unclosed_quote(line)) != 0)
	{
		new_line = readline("> ");
		if (!new_line)
		{
			ft_printf("minishell: unexpected EOF while looking for matching `%c'\n",
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
