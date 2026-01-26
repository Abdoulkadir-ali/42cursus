/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:14:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 05:20:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

char	*read_function_body(char *line, size_t n);

static size_t	count_paren_pairs(const char *s)
{
	size_t	i;
	size_t	n;
	size_t	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	i = 0;
	n = 0;
	while (i < len && s[i] == '(')
	{
		n++;
		i++;
	}
	if (n == 0)
		return (0);
	while (i < len && s[i] == ')')
		i++;
	if (i != len)
		return (0);
	if (len != n * 2)
		return (0);
	return (n);
}

char	*handle_parenthesis(char *line, char *trimmed)
{
	size_t	pairs;

	if (!trimmed || ft_strchr(line, '\n') == NULL)
		return (NULL);
	pairs = count_paren_pairs(trimmed);
	if (pairs > 0)
	{
		free(trimmed);
		line = read_function_body(line, pairs);
		return (line);
	}
	if (ft_strcmp(trimmed, "()") == 0)
	{
		free(trimmed);
		line = read_function_body(line, 1);
		return (line);
	}
	free(trimmed);
	return (NULL);
}
