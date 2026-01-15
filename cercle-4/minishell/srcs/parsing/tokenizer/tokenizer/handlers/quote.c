/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:49:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 03:40:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	scan_quoted(const char *s, char quote)
{
	int	i;
	int	closed;

	i = 1;
	closed = 0;
	while (s[i])
	{
		if (s[i] == quote)
		{
			closed = 1;
			i++;
			break ;
		}
		if (quote == '"' && s[i] == '\\' && s[i + 1])
			i++;
		i++;
	}
	if (!closed)
		return (-1);
	return (i);
}

int	scan_unquoted(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]) || ft_strchr("|<>()&", s[i]) || s[i] == ';'
			|| s[i] == '\'' || s[i] == '"')
			break ;
		if (s[i] == '\\' && s[i + 1])
			i++;
		i++;
	}
	return (i);
}
