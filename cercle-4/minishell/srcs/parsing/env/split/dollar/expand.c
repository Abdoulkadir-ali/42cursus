/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 06:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:18:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Detect `$'` or `$"` outside quotes, which suppresses expansion.
 * @param peek Lookahead information for the current dollar sign.
 * @param st Expansion quote state.
 * @return 1 when the next character is an unquoted quote, otherwise 0.
 */
static int	is_unquoted_quote(t_dollar_peek *peek, t_exp_state *st)
{
	int	b1;
	int	b2;

	b1 = (peek->next == '\'' || peek->next == '"');
	b2 = (!st->in_s_quote && !st->in_d_quote);
	if (b1 && b2)
		return (1);
	return (0);
}

/**
 * @brief Detect cases where `$` must remain literal in token output mode.
 * @param peek Lookahead information for the current dollar sign.
 * @param st Expansion quote state.
 * @return 1 when the target must not be expanded, otherwise 0.
 */
static int	is_bad_target(t_dollar_peek *peek, t_exp_state *st)
{
	if (!is_exp_target(peek->next) || st->in_s_quote || (peek->next == '"'
			&& st->in_d_quote))
		return (1);
	return (0);
}

/**
 * @brief Expand a dollar expression when writing into a plain string buffer.
 * @param in Expansion input cursor.
 * @param st Expansion quote state.
 * @param out Expansion output buffers.
 * @param peek Lookahead information for the current dollar sign.
 * @return Always returns 1 after handling the dollar sequence.
 */
int	expand_to_string(t_exp_input *in, t_exp_state *st, t_exp_output *out,
		t_dollar_peek *peek)
{
	int	should_expand;

	if (st->in_s_quote)
		should_expand = 0;
	else
		should_expand = is_exp_target(peek->next);
	if (!should_expand)
	{
		push_literal_dollar(in, out, peek->idx);
		return (1);
	}
	perform_expansion(in, st, out);
	return (1);
}

/**
 * @brief Expand a dollar expression when building split token output.
 * @param in Expansion input cursor.
 * @param st Expansion quote state.
 * @param out Expansion output buffers.
 * @param peek Lookahead information for the current dollar sign.
 * @return Always returns 1 after handling the dollar sequence.
 */
int	expand_to_tokens(t_exp_input *in, t_exp_state *st, t_exp_output *out,
		t_dollar_peek *peek)
{
	int	is_unquoted_quote_val;
	int	is_bad_target_val;

	is_unquoted_quote_val = is_unquoted_quote(peek, st);
	if (is_unquoted_quote_val)
	{
		in->pos++;
		return (1);
	}
	is_bad_target_val = is_bad_target(peek, st);
	if (is_bad_target_val)
	{
		push_literal_dollar(in, out, peek->idx);
		return (1);
	}
	perform_expansion(in, st, out);
	return (1);
}
