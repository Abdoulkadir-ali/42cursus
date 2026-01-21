/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/21 06:09:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	expand_to_string(t_exp_input *in, t_exp_state *st,
		t_exp_output *out, t_dollar_peek *peek)
{
	int	should_expand;

	should_expand = !st->in_s_quote && is_exp_target(peek->next);
	if (!should_expand)
	{
		push_literal_dollar(in, out, peek->idx);
		return (1);
	}
	perform_expansion(in, st, out);
	return (1);
}

static int	expand_to_tokens(t_exp_input *in, t_exp_state *st,
		t_exp_output *out, t_dollar_peek *peek)
{
	int	is_unquoted_quote;
	int	is_bad_target;

	is_unquoted_quote = (peek->next == '\'' || peek->next == '"')
			&& !st->in_s_quote && !st->in_d_quote;
	if (is_unquoted_quote)
	{
		in->pos++;
		return (1);
	}
	is_bad_target = !is_exp_target(peek->next) || st->in_s_quote
		|| (peek->next == '"' && st->in_d_quote);
	if (is_bad_target)
	{
		push_literal_dollar(in, out, peek->idx);
		return (1);
	}
	perform_expansion(in, st, out);
	return (1);
}

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
