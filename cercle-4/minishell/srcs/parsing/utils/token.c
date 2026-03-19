/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 02:09:03 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:31:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Check whether a token-list node has the requested type.
 * @param node Node to inspect.
 * @param type Token type to compare against.
 * @return `true` when the node exists and matches `type`, otherwise `false`.
 */
bool	cmp_node_type(t_nodes *node, t_token_type type)
{
	if (!node || !node->content)
		return (false);
	return (((t_token *)node->content)->type == type);
}

/**
 * @brief Compare a token object's type against an expected type.
 * @param tok Token object to check.
 * @param type Expected token type.
 * @return `true` when `tok` is non-NULL and `tok->type == type`.
 */
bool	cmp_tok_type(t_token *tok, t_token_type type)
{
	if (!tok)
		return (false);
	return (tok->type == type);
}

/**
 * @brief Compare an AST node's type against an expected type.
 * @param node AST node to check.
 * @param type Expected AST/token type.
 * @return `true` when `node` is non-NULL and `node->type == type`.
 */
bool	cmp_ast_type(t_ast *node, t_token_type type)
{
	if (!node)
		return (false);
	return (node->type == type);
}

/**
 * @brief Convert a linked list of token nodes into a NULL-terminated array.
 * @param list Head of the token node list.
 * @return Newly allocated array of duplicated token `value` strings, or NULL.
 */
char	**token_list_to_array(t_nodes *list)
{
	t_nodes	*it;
	int		count;
	char	**res;
	int		i;

	count = 0;
	it = list;
	while (it)
	{
		count++;
		it = it->next;
	}
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	it = list;
	i = 0;
	while (it)
	{
		res[i++] = ft_strdup(((t_token *)it->content)->value);
		it = it->next;
	}
	res[i] = NULL;
	return (res);
}

/**
 * @brief Safely free a NULL-terminated array of strings.
 * @param arr The array to free.
 * @return This function does not return a value.
 */
void	free_string_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
