/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pairs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:25:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Update the scanning state for quotes and parentheses.
 * @param c Current character being scanned.
 * @param quote Pointer to the active quote character (0 when none).
 * @param depth Pointer to the current parenthesis depth counter.
 * @return This function updates state in-place and returns no value.
 */
static void	update_scan_state(char c, char *quote, int *depth)
{
	if (*quote == 0 && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote != 0 && c == *quote)
		*quote = 0;
	else if (*quote == 0 && depth)
	{
		if (c == '(')
			(*depth)++;
		else if (c == ')')
			(*depth)--;
	}
}

/**
 * @brief Detect unmatched quote or parenthesis state in one input line.
 * @param s Input line being analyzed for continuation.
 * @param out_depth Optional output for parenthesis depth.
 * @return Quote character when unmatched, otherwise 0.
 */
char	ext_scan_pairs_state(const char *s, int *out_depth)
{
	char	quote;

	quote = 0;
	if (out_depth)
		*out_depth = 0;
	while (*s)
	{
		if (quote != '\'' && *s == '\\')
		{
			s++;
			if (*s)
				s++;
			continue ;
		}
		update_scan_state(*s, &quote, out_depth);
		s++;
	}
	return (quote);
}
