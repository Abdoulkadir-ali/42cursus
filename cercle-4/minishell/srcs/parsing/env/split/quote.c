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
 * @param exp Expansion context holding state, input, and output buffers.
 * @return This function does not return a value.
 */
static void	mark_as_quoted(t_expansion *exp)
{
	exp->has_quotes = true;
	if (exp->res_str == NULL && exp->word == NULL)
		exp->word = ft_strdup("");
}

/**
 * @brief Toggle the single-quote state when allowed by the current context.
 * @param exp Expansion context holding state, input, and output buffers.
 * @return 1 when a single quote was consumed, otherwise 0.
 */
static int	toggle_single_quote(t_expansion *exp)
{
	if (exp->in_d_quote)
		return (0);
	exp->in_s_quote = !exp->in_s_quote;
	mark_as_quoted(exp);
	exp->pos++;
	return (1);
}

/**
 * @brief Toggle the double-quote state when allowed by the current context.
 * @param exp Expansion context holding state, input, and output buffers.
 * @return 1 when a double quote was consumed, otherwise 0.
 */
static int	toggle_double_quote(t_expansion *exp)
{
	if (exp->in_s_quote)
		return (0);
	exp->in_d_quote = !exp->in_d_quote;
	mark_as_quoted(exp);
	exp->pos++;
	return (1);
}

/**
 * @brief Process one quote character while scanning an expandable word.
 * @param exp Expansion context holding state, input, and output buffers.
 * @return 1 when a quote character was handled, otherwise 0.
 */
int	handle_quote_split(t_expansion *exp)
{
	const char	c = exp->str[exp->pos];

	if (c == '\'')
		return (toggle_single_quote(exp));
	if (c == '\"')
		return (toggle_double_quote(exp));
	return (0);
}
