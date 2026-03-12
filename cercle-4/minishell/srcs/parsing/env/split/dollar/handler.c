/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:18:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Dispatch dollar handling based on the active expansion output mode.
 * @param exp Expansion context holding state, input, and output buffers.
 * @return 1 when a dollar sequence was handled, otherwise 0.
 */
int	handle_dollar_split(t_expansion *exp)
{
	t_dollar_peek	peek;

	if (exp->str[exp->pos] != '$')
		return (0);
	peek.idx = exp->pos;
	peek.next = exp->str[peek.idx + 1];
	if (exp->res_str)
		return (expand_to_string(exp, &peek));
	return (expand_to_tokens(exp, &peek));
}
