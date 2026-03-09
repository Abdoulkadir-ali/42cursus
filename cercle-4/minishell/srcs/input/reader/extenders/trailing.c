/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trailing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:39:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Detect whether the line ends with an operator requiring continuation.
 * @param line Current input line.
 * @param ops Operator definition table returned by `get_ops`.
 * @return Continuation code for the trailing operator, or 0.
 */
char	check_trailing_op(char *line, t_op_def *ops)
{
	char	*p;
	int		i;
	size_t	len;

	p = line + ft_strlen(line) - 1;
	while (p >= line && ft_isspace(*p))
		p--;
	if (p < line)
		return (0);
	if (*p == '\\' && handle_escape(line, p))
		return ('\\');
	i = 0;
	while (ops[i].code)
	{
		len = ft_strlen(ops[i].symbol);
		if (ops[i].counterpart == 0 && ops[i].code != '\\' && p - (len
				- 1) >= line && ft_strncmp(p - (len - 1), ops[i].symbol,
				len) == 0)
			return (ops[i].code);
		i++;
	}
	return (0);
}
