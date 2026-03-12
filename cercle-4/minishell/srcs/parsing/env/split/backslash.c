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
 * @param exp Expansion context holding state, input, and output buffers.
 * @return 1 when the backslash was consumed here, otherwise 0.
 */
static int	handle_dq_backslash(t_expansion *exp)
{
	char	next;

	next = exp->str[exp->pos + 1];
	if (next != '$' && next != '"' && next != '\\' && next != '\n')
	{
		exp_push_char(exp, exp->str[exp->pos]);
		exp->pos++;
		return (1);
	}
	return (0);
}

/**
 * @brief Consume a backslash escape and append the escaped character.
 * @param exp Expansion context holding state, input, and output buffers.
 * @return Always returns 1 after consuming the escape sequence.
 */
static int	consume_backslash(t_expansion *exp)
{
	char	ch;

	exp->pos++;
	if (!exp->str[exp->pos])
		return (1);
	ch = exp->str[exp->pos];
	if (!exp->in_d_quote && (ch == '*' || ch == '?'))
		exp_push_char(exp, '\001');
	exp_push_char(exp, ch);
	if (!exp->in_d_quote)
		exp->has_quotes = true;
	exp->pos++;
	return (1);
}

/**
 * @brief Process one backslash according to the current quote context.
 * @param exp Expansion context holding state, input, and output buffers.
 * @return 1 when a backslash sequence was handled, otherwise 0.
 */
int	handle_backslash_split(t_expansion *exp)
{
	if (exp->str[exp->pos] != '\\' || exp->in_s_quote)
		return (0);
	if (exp->in_d_quote)
	{
		if (handle_dq_backslash(exp))
			return (1);
	}
	return (consume_backslash(exp));
}
