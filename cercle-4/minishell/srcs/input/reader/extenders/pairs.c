/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extender_pairs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:11:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

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
