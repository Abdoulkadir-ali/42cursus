/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:45:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	mark_as_quoted(t_exp_state *st, t_exp_output *out)
{
	st->has_quotes = 1;
	if (out->str == NULL && out->word == NULL)
		out->word = ft_strdup("");
}

static int	toggle_single_quote(t_exp_input *in, t_exp_state *st,
		t_exp_output *out)
{
	if (st->in_d_quote)
		return (0);
	st->in_s_quote = !st->in_s_quote;
	mark_as_quoted(st, out);
	in->pos++;
	return (1);
}

static int	toggle_double_quote(t_exp_input *in, t_exp_state *st,
		t_exp_output *out)
{
	if (st->in_s_quote)
		return (0);
	st->in_d_quote = !st->in_d_quote;
	mark_as_quoted(st, out);
	in->pos++;
	return (1);
}

int	handle_quote_split(t_exp_input *in, t_exp_state *st, t_exp_output *out)
{
	const char	c = in->str[in->pos];

	if (c == '\'')
		return (toggle_single_quote(in, st, out));
	if (c == '\"')
		return (toggle_double_quote(in, st, out));
	return (0);
}
