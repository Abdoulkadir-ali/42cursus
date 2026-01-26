/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 05:26:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	expand_to_string(t_exp_input *in, t_exp_state *st,
		t_exp_output *out, t_dollar_peek *peek);
int	expand_to_tokens(t_exp_input *in, t_exp_state *st,
		t_exp_output *out, t_dollar_peek *peek);

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
