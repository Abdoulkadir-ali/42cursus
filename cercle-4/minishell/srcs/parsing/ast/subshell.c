/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:59:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Clone a token range into an independent token list copy.
 * @param start First token node included in the clone.
 * @param end_exclusive First token node excluded from the clone.
 * @return Newly allocated cloned token list, or NULL on allocation failure.
 */
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

/**
 * @brief Find the matching right parenthesis for a subshell token range.
 * @param start Token node expected to point at the opening parenthesis.
 * @return Token node for the matching closing parenthesis, or NULL.
 */
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

/**
 * @brief Build a subshell AST node and attach trailing redirections to it.
 * @param tokens Token list whose first token is an opening parenthesis.
 * @return Root AST node for the subshell, or NULL on failure.
 */
t_ast	*handle_subshell(t_nodes *tokens)
{
	t_nodes	*match;
	t_nodes	*inner_tokens;
	t_ast	*subshell_node;
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
