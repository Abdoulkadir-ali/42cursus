/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:01:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:50:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_match_nodes(t_nodes *matches)
{
	int	cnt;

	cnt = 0;
	while (matches)
	{
		cnt++;
		matches = matches->next;
	}
	return (cnt);
}

static void	consume_matches_to_list(t_nodes *matches, t_nodes **new_head,
		t_nodes **new_tail, t_nodes *exp_curr)
{
	t_nodes	*m_curr;
	t_nodes	*mnode;

	m_curr = matches;
	while (m_curr)
	{
		mnode = create_token_node_from_match((char *)m_curr->content);
		ft_lstadd_back(new_head, mnode);
		*new_tail = mnode;
		m_curr = m_curr->next;
	}
	ft_lstclear(&matches, free);
	del_token(exp_curr->content);
	free(exp_curr);
}

static int	is_redir_token_type(int type)
{
	return (type == TOKEN_RED_OUT || type == TOKEN_APPEND
		|| type == TOKEN_RED_IN);
}

int	process_matches_or_literal(t_token_expansion *exp, t_nodes *matches,
		t_token *exp_tok, t_nodes *exp_curr)
{
	int		is_redir_target;
	t_token	*prev_tok;

	is_redir_target = 0;
	if (exp->prev)
	{
		prev_tok = (t_token *)exp->prev->content;
		if (is_redir_token_type(prev_tok->type))
			is_redir_target = 1;
	}
	if (is_redir_target && count_match_nodes(matches) > 1)
	{
		ft_puterror("%s: ambiguous redirect\n", exp_tok->value);
		exp->expansion_error = 1;
		ft_lstclear(&matches, free);
		exp_curr->next = NULL;
		ft_lstadd_back(&exp->head, exp_curr);
		exp->tail = exp_curr;
		return (0);
	}
	consume_matches_to_list(matches, &exp->head, &exp->tail,
		exp_curr);
	return (1);
}
