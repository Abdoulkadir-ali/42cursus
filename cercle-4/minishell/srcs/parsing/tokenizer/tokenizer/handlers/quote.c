/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:49:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:24:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Scan the length of a quoted fragment including its closing quote.
 * @param s Pointer to the opening quote in the source string.
 * @param quote Quote character being matched.
 * @return Fragment length, or -1 when the quote never closes.
 */
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

/**
 * @brief Scan the length of an unquoted word fragment.
 * @param s Pointer to the current scan position.
 * @return Number of characters that belong to the same unquoted fragment.
 */
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
