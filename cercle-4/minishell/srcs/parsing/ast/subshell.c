/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 00:38:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_nodes	*clone_tokens_range(t_nodes *start, t_nodes *end_exclusive)
{
	t_nodes	*res;
	t_nodes	*it;
	t_token	*t;
	t_token	*copy;

	res = NULL;
	it = start;
	while (it && it != end_exclusive)
	{
		t = (t_token *)it->content;
		copy = ft_calloc(1, sizeof(t_token));
		if (!copy)
			return (NULL);
		if (t->value)
			copy->value = ft_strdup(t->value);
		copy->type = t->type;
		copy->quoted = t->quoted;
		copy->expanded = t->expanded;
		ft_lstadd_back(&res, ft_lstnew(copy));
		it = it->next;
	}
	return (res);
}

static t_nodes	*find_match(t_nodes *start)
{
	t_nodes	*scan;
	t_token	*tk;
	int		depth;

	scan = start;
	depth = 0;
	while (scan)
	{
		tk = (t_token *)scan->content;
		if (tk->type == TOKEN_LPAREN)
			depth++;
		else if (tk->type == TOKEN_RPAREN)
		{
			depth--;
			if (depth == 0)
				return (scan);
		}
		scan = scan->next;
	}
	return (NULL);
}

t_nodes	*handle_subshell(t_nodes *tokens)
{
	t_nodes	*match;
	t_nodes	*inner_tokens;
	t_nodes	*subshell_node;
	t_nodes	*remaining;

	match = find_match(tokens);
	if (!match)
	{
		ft_lstclear(&tokens, del_token);
		return (NULL);
	}
	inner_tokens = clone_tokens_range(tokens->next, match);
	subshell_node = create_node(TOKEN_SUBSHELL, NULL, ast_builder(inner_tokens),
			NULL);
	remaining = clone_tokens_range(match->next, NULL);
	subshell_node = process_redirections(subshell_node, remaining);
	ft_lstclear(&tokens, del_token);
	ft_lstclear(&remaining, del_token);
	return (subshell_node);
}
