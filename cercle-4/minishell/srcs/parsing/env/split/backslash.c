/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 14:20:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	handle_dq_backslash(t_exp_input *in, t_exp_output *out)
{
	char	next;

	next = in->str[in->pos + 1];
	if (next != '$' && next != '"' && next != '\\' && next != '\n')
	{
		exp_push_char(out, in->str[in->pos]);
		in->pos++;
		return (1);
	}
	return (0);
}

static int	consume_backslash(t_exp_input *in, t_exp_state *st,
		t_exp_output *out)
{
	in->pos++;
	if (!in->str[in->pos])
		return (1);
	exp_push_char(out, in->str[in->pos]);
	if (!st->in_d_quote)
		st->has_quotes = 1;
	in->pos++;
	return (1);
}

int	handle_backslash_split(t_exp_input *in, t_exp_state *st, t_exp_output *out)
{
	if (in->str[in->pos] != '\\' || st->in_s_quote)
		return (0);
	if (st->in_d_quote)
	{
		if (handle_dq_backslash(in, out))
			return (1);
	}
	return (consume_backslash(in, st, out));
}
