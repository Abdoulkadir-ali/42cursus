/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:15:13 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/09 03:47:07 by abdoali          ###   ########.fr       */
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

char	*append_line(char *line, char *new_line, char code)
{
	int	len;
	int	i;

	if (!line || !new_line)
		return (NULL);
	len = ft_strlen(line);
	i = len - 1;
	while (i >= 0 && ft_isspace(line[i]))
		i--;
	if (code == '\\' && i >= 0 && line[i] == '\\')
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
