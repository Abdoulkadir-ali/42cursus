/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:18:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Handle backslashes that appear inside double quotes.
 * @param in Expansion input cursor.
 * @param out Expansion output buffers.
 * @return 1 when the backslash was consumed here, otherwise 0.
 */
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

/**
 * @brief Consume a backslash escape and append the escaped character.
 * @param in Expansion input cursor.
 * @param st Expansion quote state.
 * @param out Expansion output buffers.
 * @return Always returns 1 after consuming the escape sequence.
 */
static int	consume_backslash(t_exp_input *in, t_exp_state *st,
		t_exp_output *out)
{
	char	ch;

	in->pos++;
	if (!in->str[in->pos])
		return (1);
	ch = in->str[in->pos];
	if (!st->in_d_quote && (ch == '*' || ch == '?'))
		exp_push_char(out, '\001');
	exp_push_char(out, ch);
	if (!st->in_d_quote)
		st->has_quotes = 1;
	in->pos++;
	return (1);
}

/**
 * @brief Process one backslash according to the current quote context.
 * @param in Expansion input cursor.
 * @param st Expansion quote state.
 * @param out Expansion output buffers.
 * @return 1 when a backslash sequence was handled, otherwise 0.
 */
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
