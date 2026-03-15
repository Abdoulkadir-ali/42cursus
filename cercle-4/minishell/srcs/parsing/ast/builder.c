/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:10:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/03/15 00:19:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Recursively release an AST and all dynamically allocated members.
 * @param ast_node Root of the AST subtree to free.
 * @return This function does not return a value.
 */
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

/**
 * @brief Find the next top-level split operator while skipping parentheses.
 * @param tokens Token list currently being converted into an AST.
 * @param t1 First token type accepted as a split operator.
 * @param t2 Optional second token type accepted as a split operator.
 * @param prev_out Output slot receiving the node before the split token.
 * @return Pointer to the matching split node, or NULL when none exists.
 */
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

/**
 * @brief Build one AST operator node around a chosen split token.
 * @param left_toks Token list belonging to the left subtree.
 * @param split Token node selected as the root operator.
 * @return Newly allocated AST operator node, or NULL on allocation failure.
 */
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

/**
 * @brief Convert a token list into the corresponding AST subtree.
 * @param tokens Token list for one command segment.
 * @return Root of the constructed AST subtree, or NULL when empty.
 */
t_ast	*ast_builder(t_nodes *tokens)
{
	t_nodes	*split;
	t_nodes	*prev;

	if (!tokens)
		return (NULL);
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
