/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 07:09:27 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:39:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Detect unmatched quote or parenthesis state in one input line.
 * @param s Input line being analyzed for continuation.
 * @return Quote character, `p` for open parenthesis depth, or 0.
 */
static char	check_pairs_state(char *s)
{
	char	quote;
	int		depth;

	if (!s)
		return (0);
	quote = check_quote_state(s);
	if (quote != 0)
		return (quote);
	depth = check_parenthesis_state(s);
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
