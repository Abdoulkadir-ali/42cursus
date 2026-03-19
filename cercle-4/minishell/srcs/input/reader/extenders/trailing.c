/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trailing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:43:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Check whether a symbol string is composed of the same repeating char.
 * @param sym Symbol string to inspect.
 * @param len Length of the symbol string.
 * @return `true` when all characters match the first, otherwise `false`.
 */
static bool	is_repeating_symbol(const char *sym, size_t len)
{
	size_t	i;

	if (!sym || len < 2)
		return (false);
	i = 1;
	while (i < len)
	{
		if (sym[i] != sym[0])
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Decide whether a detected trailing operator should be ignored.
 *	This suppresses continuation when the operator is a repeated symbol
 *	and is itself part of a longer repetition immediately before the match.
 * @param op Operator definition being considered.
 * @param p Pointer to the current scan position in the line.
 * @param line Start of the input line buffer.
 * @param len Length of the operator symbol.
 * @return `true` when continuation should be suppressed,
 otherwise `false`.
*/
static bool	should_suppress_continuation(t_op_def *op, char *p, char *line,
		size_t len)
{
	if (!op || !p || !line)
		return (false);
	if (!is_repeating_symbol(op->symbol, len))
		return (false);
	if (p - (len - 1) <= line)
		return (false);
	if (*(p - len) == op->symbol[0])
		return (true);
	return (false);
}

/**
 * @brief Scan operator table to find a trailing operator at the end of line.
 * @param p Pointer to the last non-space character in the line.
 * @param ops Operator table returned by `get_ops()`.
 * @param line Start of the input line buffer.
 * @return Continuation code for the matching operator, or 0 when none.
 */
static char	scan_ops_for_trailing(char *p, t_op_def *ops, char *line)
{
	int		i;
	size_t	len;

	i = 0;
	if (!line || !p)
		return (0);
	if (*p == '\\' && handle_escape(line, p))
		return ('\\');
	while (ops[i].code)
	{
		len = ft_strlen(ops[i].symbol);
		if (ops[i].counterpart == 0 && ops[i].code != '\\' && p - (len
				- 1) >= line && ft_strncmp(p - (len - 1), ops[i].symbol,
				len) == 0)
		{
			if (should_suppress_continuation(&ops[i], p, line, len))
			{
				i++;
				continue ;
			}
			return (ops[i].code);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Detect whether the line ends with an operator requiring continuation.
 * @param line Current input line.
 * @param ops Operator definition table returned by `get_ops`.
 * @return Continuation code for the trailing operator, or 0.
 */
char	check_trailing_op(char *line, t_op_def *ops)
{
	char	*p;

	p = find_last_non_space(line);
	if (!p)
		return (0);
	return (scan_ops_for_trailing(p, ops, line));
}
