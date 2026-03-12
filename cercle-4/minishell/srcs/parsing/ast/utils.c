/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:59:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:59:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Allocate and initialize one AST node.
 * @param type Token type represented by the new AST node.
 * @param args Argument array owned by the new node.
 * @param left Left child subtree.
 * @param right Right child subtree.
 * @return Newly allocated AST node, or NULL on allocation failure.
 */
t_ast	*create_node(t_token_type type, char **args, t_ast *left,
		t_ast *right)
{
	t_ast	*ast;

	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->type = type;
	ast->args = args;
	ast->left = left;
	ast->right = right;
	ast->is_quoted = 0;
	return (ast);
}

/**
 * @brief Append one expanded word token to a token list under construction.
 * @param head Address of the token-list head.
 * @param tail Address of the token-list tail.
 * @param val Word string already owned by the caller or expansion logic.
 * @param quoted Quote flag copied into the new token.
 * @return This function does not return a value.
 */
void	add_token_node(t_nodes **head, t_nodes **tail, char *val, bool quoted)
{
	t_token	*tok;
	t_nodes	*node;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return ;
	tok->type = TOKEN_WORD;
	tok->value = val;
	tok->quoted = quoted;
	tok->expanded = 1;
	node = ft_lstnew(tok);
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
}
