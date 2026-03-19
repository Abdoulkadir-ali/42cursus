/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 06:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:42:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Unified dollar expansion handler for both string and token modes.
 * @param exp Expansion context.
 * @return 1 if handled, 0 otherwise.
 */
int	handle_dollar_split(t_expansion *exp)
{
	t_token_type	next;

	if (!is_dollar_start(exp, &next))
		return (0);
	if (exp->in_s_quote)
		return (handle_in_s_quote(exp));
	if (!exp->res_str && !exp->in_d_quote && (next == '\'' || next == '"'))
		return (handle_quote_after_dollar(exp));
	if (!is_exp_target(next) || (next == '"' && exp->in_d_quote))
		return (handle_non_target_or_dquote(exp, next));
	perform_expansion(exp);
	return (1);
}

/**
 * @brief Detect whether the current position starts a dollar expansion.
 * @param exp Expansion context containing the input string and position.
 * @param next Out parameter receiving the next character after '$'.
 * @return 1 when a dollar sign is present at the current position, else 0.
 */
int	is_dollar_start(t_expansion *exp, t_token_type *next)
{
	if (exp->str[exp->pos] != '$')
		return (0);
	*next = exp->str[exp->pos + 1];
	return (1);
}

/**
 * @brief Handle a dollar sign encountered inside single quotes.
 * @param exp Expansion context.
 * @return 1 when handled.
 */
int	handle_in_s_quote(t_expansion *exp)
{
	exp_push_char(exp, '$');
	exp->pos++;
	return (1);
}

/**
 * @brief Handle a quoted delimiter immediately following a dollar.
 * @param exp Expansion context.
 * @return 1 when handled.
 */
int	handle_quote_after_dollar(t_expansion *exp)
{
	exp->pos++;
	return (1);
}

/**
 * @brief Handle cases where the dollar is not an expansion target.
 * @param exp Expansion context.
 * @param next The upcoming character after '$'.
 * @return 1 when handled.
 */
int	handle_non_target_or_dquote(t_expansion *exp, t_token_type next)
{
	(void)next;
	exp_push_char(exp, '$');
	exp->pos++;
	return (1);
}
