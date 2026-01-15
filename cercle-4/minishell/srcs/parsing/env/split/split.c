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

t_nodes	*finalize_expansion(t_exp_buffers *buf, t_exp_quotes *quotes)
{
	if (buf->word)
		add_token_node(&buf->head, &buf->tail, buf->word,
			quotes->was_quoted);
	else if (quotes->was_quoted)
		add_token_node(&buf->head, &buf->tail, ft_strdup(""), 1);
	return (buf->head);
}

static void	run_expansion_loop(t_expansion *exp)
{
	while (exp->params.str[exp->params.pos])
	{
		if (handle_quote_split(&exp->params, &exp->quotes, &exp->buffers))
			continue ;
		if (handle_backslash_split(&exp->params, &exp->quotes, &exp->buffers))
			continue ;
		if (handle_dollar_split(&exp->params, &exp->quotes, &exp->buffers))
			continue ;
		append_chunk(&exp->buffers.word, ft_substr(exp->params.str,
				exp->params.pos, 1));
		if (!exp->quotes.s_quote && !exp->quotes.d_quote)
			exp->quotes.was_quoted = 0;
		exp->params.pos++;
	}
}

t_nodes	*expand_and_split(char *str, char **env, int status)
{
	t_expansion	exp;

	if (!str)
		return (NULL);
	ft_bzero(&exp, sizeof(t_expansion));
	exp.params.str = str;
	exp.params.env = env;
	exp.params.status = status;
	run_expansion_loop(&exp);
	return (finalize_expansion(&exp.buffers, &exp.quotes));
}
