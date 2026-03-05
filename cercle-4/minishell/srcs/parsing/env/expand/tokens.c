/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:01:48 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 23:01:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	process_expanded_list(t_token_expansion *exp,
		t_nodes *expanded_list)
{
	t_nodes	*exp_curr;
	t_nodes	*exp_next;
	t_token	*exp_tok;
	t_nodes	*matches;

	exp_curr = expanded_list;
	while (exp_curr)
	{
		exp_next = exp_curr->next;
		exp_tok = (t_token *)exp_curr->content;
		exp_tok->type = TOKEN_WORD;
		if (!exp_tok->quoted && ft_strchr(exp_tok->value, '*'))
		{
			matches = expand_wildcard(exp_tok->value);
			if (matches)
				process_matches_or_literal(exp, matches, exp_tok, exp_curr);
			else
				append_node(&exp->head, &exp->tail, exp_curr);
		}
		else
			append_node(&exp->head, &exp->tail, exp_curr);
		exp_curr = exp_next;
	}
}

static void	handle_word_node(t_token_expansion *exp, t_nodes *curr,
		char **env, int status)
{
	t_token	*tok;
	t_nodes	*expanded_list;

	tok = (t_token *)curr->content;
	if (is_prev_heredoc(exp->prev))
	{
		append_node(&exp->head, &exp->tail, curr);
		exp->prev = exp->tail;
		return ;
	}
	apply_tilde_expansion(tok, env);
	expanded_list = expand_and_split(tok->value, env, status);
	process_expanded_list(exp, expanded_list);
	del_token(curr->content);
	free(curr);
}

int	expand_tokens(t_nodes **tokens, char **env, int status)
{
	t_token_expansion	exp;
	t_nodes				*curr;
	t_nodes				*next;

	ft_bzero(&exp, sizeof(exp));
	curr = *tokens;
	while (curr)
	{
		next = curr->next;
		if (((t_token *)curr->content)->type == TOKEN_WORD)
			handle_word_node(&exp, curr, env, status);
		else
		{
			append_node(&exp.head, &exp.tail, curr);
			exp.prev = exp.tail;
		}
		curr = next;
		if (exp.prev == NULL && exp.tail)
			exp.prev = exp.tail;
	}
	*tokens = exp.head;
	return (exp.expansion_error);
}
