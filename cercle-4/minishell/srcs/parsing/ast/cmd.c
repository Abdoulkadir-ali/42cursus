/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:05:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/01/15 04:43:26 by abdoali          ###   ########.fr       */
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

static t_nodes	*handle_subshell(t_nodes *tokens)
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

static t_nodes	*handle_simple_cmd(t_nodes *tokens)
{
	t_nodes	*curr;
	char	**args;
	int		count;
	int		i;
	t_nodes	*node;

	count = 0;
	curr = tokens;
	while (curr)
	{
		if (((t_token *)curr->content)->type == TOKEN_WORD)
			count++;
		else if (((t_token *)curr->content)->type != TOKEN_PIPE && curr->next)
			curr = curr->next;
		curr = curr->next;
	}
	args = ft_calloc(count + 1, sizeof(char *));
	i = 0;
	curr = tokens;
	while (curr)
	{
		if (((t_token *)curr->content)->type == TOKEN_WORD)
			args[i++] = ft_strdup(((t_token *)curr->content)->value);
		else if (((t_token *)curr->content)->type != TOKEN_PIPE && curr->next)
			curr = curr->next;
		curr = curr->next;
	}
	node = create_node(TOKEN_WORD, args, NULL, NULL);
	curr = tokens;
	while (curr)
	{
		if (((t_token *)curr->content)->type == TOKEN_WORD)
		{
			((t_ast *)node->content)->is_quoted = ((t_token *)curr->content)->quoted;
			break ;
		}
		curr = curr->next;
	}
	node = process_redirections(node, tokens);
	ft_lstclear(&tokens, del_token);
	return (node);
}

t_nodes	*create_cmd_node(t_nodes *tokens)
{
	t_nodes	*curr;

	curr = tokens;
	if (curr && ((t_token *)curr->content)->type == TOKEN_LPAREN)
		return (handle_subshell(tokens));
	return (handle_simple_cmd(tokens));
}
