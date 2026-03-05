/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 07:09:27 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:12:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

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
