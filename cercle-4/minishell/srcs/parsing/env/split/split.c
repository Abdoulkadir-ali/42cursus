/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:37:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_nodes	*finalize_expansion(t_exp_output *out, t_exp_state *st)
{
	if (out->word)
		add_token_node(&out->head, &out->tail, out->word,
			st->has_quotes);
	else if (st->has_quotes)
		add_token_node(&out->head, &out->tail, ft_strdup(""), 1);
	return (out->head);
}

static void	run_expansion_loop(t_expansion *exp)
{
	while (exp->input.str[exp->input.pos])
	{
		if (handle_quote_split(&exp->input, &exp->state, &exp->output))
			continue ;
		if (handle_backslash_split(&exp->input, &exp->state, &exp->output))
			continue ;
		if (handle_dollar_split(&exp->input, &exp->state, &exp->output))
			continue ;
		exp_push_char(&exp->output, exp->input.str[exp->input.pos]);
		if (!exp->state.in_s_quote && !exp->state.in_d_quote)
			exp->state.has_quotes = 0;
		exp->input.pos++;
	}
}

t_nodes	*expand_and_split(char *str, char **env, int status)
{
	t_expansion	exp;

	if (!str)
		return (NULL);
	ft_bzero(&exp, sizeof(t_expansion));
	exp.input.str = str;
	exp.input.env = env;
	exp.input.status = status;
	run_expansion_loop(&exp);
	return (finalize_expansion(&exp.output, &exp.state));
}
