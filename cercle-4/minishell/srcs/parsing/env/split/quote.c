/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:28:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Toggle a quote state (single or double) and mark as quoted.
 * @param exp Expansion context.
 * @param in_quote Pointer to the boolean quote state to toggle.
 * @param check_quote The other quote state that must be false.
 * @return 1 on success, 0 if blocked by the other quote type.
 */
static int	toggle_quote(t_expansion *exp, bool *in_quote, bool check_quote)
{
	if (check_quote)
		return (0);
	*in_quote = !*in_quote;
	exp->has_quotes = true;
	if (!exp->res_str && !exp->word)
		exp->word = ft_strdup("");
	exp->pos++;
	return (1);
}

/**
 * @brief Entry point to handle quote characters during splitting.
 * @param exp Expansion context containing the input and state flags.
 * @return 1 when a quote was processed, 0 otherwise.
 */
int	handle_quote_split(t_expansion *exp)
{
	if (exp->str[exp->pos] == '\'')
		return (toggle_quote(exp, &exp->in_s_quote, exp->in_d_quote));
	if (exp->str[exp->pos] == '"')
		return (toggle_quote(exp, &exp->in_d_quote, exp->in_s_quote));
	return (0);
}
