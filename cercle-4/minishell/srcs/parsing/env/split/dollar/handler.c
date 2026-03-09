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
 * @param in Expansion input cursor.
 * @param st Expansion quote state.
 * @param out Expansion output buffers.
 * @return 1 when a dollar sequence was handled, otherwise 0.
 */
int	handle_dollar_split(t_exp_input *in, t_exp_state *st, t_exp_output *out)
{
	t_dollar_peek	peek;

	if (in->str[in->pos] != '$')
		return (0);
	peek.idx = in->pos;
	peek.next = in->str[peek.idx + 1];
	if (out->str)
		return (expand_to_string(in, st, out, &peek));
	return (expand_to_tokens(in, st, out, &peek));
}
