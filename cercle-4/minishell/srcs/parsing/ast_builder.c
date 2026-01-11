/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:59:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 05:20:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast(t_nodes *ast_node)
{
	t_ast	*ast;
	int		i;

	if (!ast_node)
		return ;
	ast = (t_ast *)ast_node->content;
	if (ast->left)
		free_ast(ast->left);
	if (ast->right)
		free_ast(ast->right);
	if (ast->args)
	{
		i = 0;
		while (ast->args[i])
		{
			free(ast->args[i]);
			i++;
		}
		free(ast->args);
	}
	free(ast);
	free(ast_node);
}

static t_nodes	*create_cmd_node(t_nodes *tokens)
{
	t_ast	*ast_data;
	int		count;
	int		i;
	t_token	*tok;

	debug_printf("AST: Creating CMD node\n");
	ast_data = ft_calloc(1, sizeof(t_ast));
	if (!ast_data)
		return (NULL);
	ast_data->type = TOKEN_WORD;
	count = ft_lstsize(tokens);
	ast_data->args = ft_calloc(count + 1, sizeof(char *));
	if (!ast_data->args)
	{
		free(ast_data);
		return (NULL);
	}
	i = 0;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (tok->type == TOKEN_WORD || tok->type == TOKEN_RED_IN
			|| tok->type == TOKEN_RED_OUT)
			ast_data->args[i++] = ft_strdup(tok->value);
		tokens = tokens->next;
	}
	return (ft_lstnew(ast_data));
}

t_nodes	*ast_builder(t_nodes *tokens)
{
	t_nodes	*cursor;
	t_nodes	*prev;
	t_token	*tok;
	t_ast	*ast_data;

	if (!tokens)
		return (NULL);
	cursor = tokens;
	prev = NULL;
	while (cursor)
	{
		tok = (t_token *)cursor->content;
		if (tok->type == TOKEN_PIPE)
		{
			debug_printf("AST: Found PIPE\n");
			if (prev)
				prev->next = NULL;
			else
				tokens = NULL;
			ast_data = ft_calloc(1, sizeof(t_ast));
			if (!ast_data)
				return (NULL);
			ast_data->type = TOKEN_PIPE;
			ast_data->left = ast_builder(tokens);
			ast_data->right = ast_builder(cursor->next);
			return (ft_lstnew(ast_data));
		}
		prev = cursor;
		cursor = cursor->next;
	}
	return (create_cmd_node(tokens));
}
