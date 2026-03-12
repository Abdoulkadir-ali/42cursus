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
 * @param exp Expansion context holding state, input, and output buffers.
 * @return True when the next character is an unquoted quote, otherwise false.
 */
static bool	is_unquoted_quote(t_dollar_peek *peek, t_expansion *exp)
{
	bool	b1;
	bool	b2;

	b1 = (peek->next == '\'' || peek->next == '"');
	b2 = (!exp->in_s_quote && !exp->in_d_quote);
	if (b1 && b2)
		return (true);
	return (false);
}

/**
 * @brief Detect cases where `$` must remain literal in token output mode.
 * @param peek Lookahead information for the current dollar sign.
 * @param exp Expansion context holding state, input, and output buffers.
 * @return True when the target must not be expanded, otherwise false.
 */
static bool	is_bad_target(t_dollar_peek *peek, t_expansion *exp)
{
	if (!is_exp_target(peek->next) || exp->in_s_quote || (peek->next == '"'
			&& exp->in_d_quote))
		return (true);
	return (false);
}

/**
 * @brief Expand a dollar expression when writing into a plain string buffer.
 * @param exp Expansion context holding state, input, and output buffers.
 * @param peek Lookahead information for the current dollar sign.
 * @return Always returns 1 after handling the dollar sequence.
 */
int	expand_to_string(t_expansion *exp, t_dollar_peek *peek)
{
	bool	should_expand;

	if (exp->in_s_quote)
		should_expand = false;
	else
		should_expand = is_exp_target(peek->next);
	if (!should_expand)
	{
		push_literal_dollar(exp, peek->idx);
		return (1);
	}
	perform_expansion(exp);
	return (1);
}

/**
 * @brief Expand a dollar expression when building split token output.
 * @param exp Expansion context holding state, input, and output buffers.
 * @param peek Lookahead information for the current dollar sign.
 * @return Always returns 1 after handling the dollar sequence.
 */
int	expand_to_tokens(t_expansion *exp, t_dollar_peek *peek)
{
	bool	is_unquoted_quote_val;
	bool	is_bad_target_val;

	is_unquoted_quote_val = is_unquoted_quote(peek, exp);
	if (is_unquoted_quote_val)
	{
		exp->pos++;
		return (1);
	}
	is_bad_target_val = is_bad_target(peek, exp);
	if (is_bad_target_val)
	{
		push_literal_dollar(exp, peek->idx);
		return (1);
	}
	perform_expansion(exp);
	return (1);
}
