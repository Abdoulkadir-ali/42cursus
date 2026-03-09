/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pairs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:39:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Check whether the line ends inside a still-open quote context.
 * @param s Input line being scanned.
 * @return Open quote character when unmatched, otherwise 0.
 */
char	check_quote_state(const char *s)
{
	char	quote;

	quote = 0;
	while (*s)
	{
		if (quote != '\'' && *s == '\\')
		{
			s++;
			if (*s)
				s++;
			continue ;
		}
		if (quote == 0 && (*s == '\'' || *s == '"'))
			quote = *s;
		else if (quote != 0 && *s == quote)
			quote = 0;
		s++;
	}
	return (quote);
}

/**
 * @brief Compute the unmatched parenthesis depth outside quoted text.
 * @param s Input line being scanned.
 * @return Final parenthesis depth after scanning the full input line.
 */
int	check_parenthesis_state(const char *s)
{
	int		depth;
	char	quote;

	depth = 0;
	quote = 0;
	while (*s)
	{
		if (quote != '\'' && *s == '\\')
		{
			s++;
			if (*s)
				s++;
			continue ;
		}
		if (quote == 0 && (*s == '\'' || *s == '"'))
			quote = *s;
		else if (quote == 0 && *s == '(')
			depth++;
		else if (quote == 0 && *s == ')')
			depth--;
		else if (quote != 0 && *s == quote)
			quote = 0;
		s++;
	}
	return (depth);
}
