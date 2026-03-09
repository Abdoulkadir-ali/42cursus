/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:18:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Record that the current expansion path has passed through quotes.
 * @param st Expansion quote state.
 * @param out Expansion output buffers.
 * @return This function does not return a value.
 */
static void	mark_as_quoted(t_exp_state *st, t_exp_output *out)
{
	st->has_quotes = 1;
	if (out->str == NULL && out->word == NULL)
		out->word = ft_strdup("");
}

/**
 * @brief Toggle the single-quote state when allowed by the current context.
 * @param in Expansion input cursor.
 * @param st Expansion quote state.
 * @param out Expansion output buffers.
 * @return 1 when a single quote was consumed, otherwise 0.
 */
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

/**
 * @brief Toggle the double-quote state when allowed by the current context.
 * @param in Expansion input cursor.
 * @param st Expansion quote state.
 * @param out Expansion output buffers.
 * @return 1 when a double quote was consumed, otherwise 0.
 */
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

/**
 * @brief Process one quote character while scanning an expandable word.
 * @param in Expansion input cursor.
 * @param st Expansion quote state.
 * @param out Expansion output buffers.
 * @return 1 when a quote character was handled, otherwise 0.
 */
int	handle_quote_split(t_exp_input *in, t_exp_state *st, t_exp_output *out)
{
	const char	c = in->str[in->pos];

	if (c == '\'')
		return (toggle_single_quote(in, st, out));
	if (c == '\"')
		return (toggle_double_quote(in, st, out));
	return (0);
}
