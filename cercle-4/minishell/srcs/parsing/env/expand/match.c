/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:01:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:48:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Count how many wildcard matches were produced for one token.
 * @param matches Linked list of matched path strings.
 * @return Number of nodes stored in the match list.
 */
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

/**
 * @brief Convert wildcard match into token nodes and consume the source token.
 * @param matches Linked list of matched path strings.
 * @param new_head Output token-list head receiving the converted nodes.
 * @param new_tail Output token-list tail receiving the converted nodes.
 * @param exp_curr Original expanded token node being replaced.
 * @return This function does not return a value.
 */
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

/**
 * @brief Check whether a token type names a redirection operator.
 * @param type Token type under inspection.
 * @return 1 for supported redirection token types, otherwise 0.
 */
static int	is_redir_token_type(int type)
{
	return (type == TOKEN_RED_OUT || type == TOKEN_APPEND
		|| type == TOKEN_RED_IN);
}

/**
 * @brief Apply wildcard matches or keep the literal token after expansion.
 * @param exp Token-expansion context being rebuilt.
 * @param matches Linked list of wildcard matches for the current token.
 * @param exp_tok Expanded token content under consideration.
 * @param exp_curr Token-list node currently being processed.
 * @return 1 on success, 0 when expansion triggers an ambiguous redirect error.
 */
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
