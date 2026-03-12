/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:18:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Finalize the current expansion result into a token list.
 * @param out Expansion output buffers and token-list accumulator.
 * @param st Expansion quote state.
 * @return Head of the token list produced by expansion.
 */
static t_nodes	*finalize_expansion(t_expansion *exp)
{
	if (exp->word)
		add_token_node(&exp->head, &exp->tail, exp->word,
			exp->has_quotes);
	else if (exp->has_quotes)
		add_token_node(&exp->head, &exp->tail, ft_strdup(""), true);
	return (exp->head);
}

/**
 * @brief Run the character-by-character split and expansion loop.
 * @param exp Full expansion context containing input, state, and output.
 * @return This function does not return a value.
 */
static void	run_expansion_loop(t_expansion *exp)
{
	while (exp->str[exp->pos])
	{
		if (handle_quote_split(exp))
			continue ;
		if (handle_backslash_split(exp))
			continue ;
		if (handle_dollar_split(exp))
			continue ;
		if ((exp->in_s_quote || exp->in_d_quote)
			&& (exp->str[exp->pos] == '*'
				|| exp->str[exp->pos] == '?'))
			exp_push_char(exp, '\001');
		exp_push_char(exp, exp->str[exp->pos]);
		if (!exp->in_s_quote && !exp->in_d_quote)
			exp->has_quotes = false;
		exp->pos++;
	}
}

/**
 * @brief Expand one word into a token list with quote-aware field splitting.
 * @param str Source word string.
 * @param env Environment array used for expansion.
 * @param status Last shell exit status.
 * @return Head of the token list produced by expansion.
 */
t_nodes	*expand_and_split(char *str, char **env, int status)
{
	t_expansion	exp;

	if (!str)
		return (NULL);
	ft_bzero(&exp, sizeof(t_expansion));
	exp.str = str;
	exp.env = env;
	exp.status = status;
	run_expansion_loop(&exp);
	return (finalize_expansion(&exp));
}
