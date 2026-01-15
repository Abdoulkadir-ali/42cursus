/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 14:20:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_exp_target(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

static void	perform_expansion(t_exp_input *in, t_exp_state *st, t_exp_output *out)
{
	char	*val;

	val = handle_dollar((char *)in->str, &in->pos, in->env, in->status);
	if (out->str)
		exp_push_str(out, val);
	else if (st->in_d_quote)
	{
		exp_push_str(out, val);
		st->has_quotes = 1;
	}
	else
	{
		process_val_split(val, out);
		free(val);
	}
}

static void	push_literal_dollar(t_exp_input *in, t_exp_output *out, int idx)
{
	exp_push_char(out, in->str[idx]);
	in->pos++;
}

static int	expand_to_string(t_exp_input *in, t_exp_state *st, t_exp_output *out,
		t_dollar_peek *peek)
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

static int	expand_to_tokens(t_exp_input *in, t_exp_state *st, t_exp_output *out,
		t_dollar_peek *peek)
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
