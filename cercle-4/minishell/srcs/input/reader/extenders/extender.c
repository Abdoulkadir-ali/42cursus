/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 07:09:27 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:25:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Determine whether the given line has unmatched pairs or quotes.
 * @param s Input string to scan.
 * @return Non-zero continuation code: quote char when a quote is open,
 *         'p' when parentheses are unclosed, or 0 when balanced.
 */
static char	check_pairs_state(char *s)
{
	char	quote;
	int		depth;

	if (!s)
		return (0);
	quote = ext_scan_pairs_state(s, &depth);
	if (quote != 0)
		return (quote);
	if (depth > 0)
		return ('p');
	return (0);
}

/**
 * @brief Analyze one line and decide whether multiline extension is needed.
 * @param line Current input line.
 * @return Continuation code describing the missing closing construct, or 0.
 */
char	ext_analyze_input(char *line)
{
	char		state_code;
	t_op_def	*ops;

	ops = get_ops();
	state_code = check_pairs_state(line);
	if (state_code != 0)
		return (state_code);
	return (check_trailing_op(line, ops));
}
