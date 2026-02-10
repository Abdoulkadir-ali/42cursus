/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:10:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/09 04:12:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_ast(t_ast *ast_node)
{
	int	i;

	if (!ast_node)
		return ;
	if (ast_node->left)
		free_ast(ast_node->left);
	if (ast_node->right)
		free_ast(ast_node->right);
	if (ast_node->args)
	{
		i = 0;
		while (ast_node->args[i])
			free(ast_node->args[i++]);
		free(ast_node->args);
	}
	free(ast_node);
}

static t_nodes	*find_split(t_nodes *tokens, t_token_type t1, t_token_type t2,
		t_nodes **prev_out)
{
	t_nodes	*curr;
	t_nodes	*prev;
	int		d;
	t_token	*t;

	curr = tokens;
	prev = NULL;
	d = 0;
	while (curr)
	{
		t = (t_token *)curr->content;
		if (t->type == TOKEN_LPAREN)
			d++;
		else if (t->type == TOKEN_RPAREN)
			d--;
		else if (d == 0 && (t->type == t1 || (t2 && t->type == t2)))
		{
			if (prev_out)
				*prev_out = prev;
			return (curr);
		}
		prev = curr;
		curr = curr->next;
	}
	return (NULL);
}

static t_ast	*build_op(t_nodes *left_toks, t_nodes *split)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = ((t_token *)split->content)->type;
	node->left = ast_builder(left_toks);
	node->right = ast_builder(split->next);
	del_token(split->content);
	free(split);
	return (node);
}

t_ast	*ast_builder(t_nodes *tokens)
{
	t_nodes	*split;
	t_nodes	*prev;

	if (!tokens)
		return (NULL);
	split = find_split(tokens, TOKEN_RPAREN, TOKEN_LPAREN, &prev);
	if (!split)
		split = find_split(tokens, TOKEN_AND, 0, &prev);
	if (!split)
		split = find_split(tokens, TOKEN_OR, 0, &prev);
	if (!split)
		split = find_split(tokens, TOKEN_PIPE, TOKEN_SEMICOLON, &prev);
	if (split)
	{
		if (prev)
			prev->next = NULL;
		else
			tokens = NULL;
		return (build_op(tokens, split));
	}
	return (create_cmd_node(tokens));
}
