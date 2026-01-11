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

#include "parsing.h"

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

static t_nodes	*create_node(t_token_type type, char **args, t_nodes *left, t_nodes *right)
{
	t_ast	*ast;

	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->type = type;
	ast->args = args;
	ast->left = left;
	ast->right = right;
	return (ft_lstnew(ast));
}

static t_nodes	*process_redirections(t_nodes *cmd_node, t_nodes *tokens)
{
	t_nodes	*curr;
	t_token	*tok;
	t_nodes	*redir_node;
	char	**args;

	curr = tokens;
	while (curr)
	{
		tok = (t_token *)curr->content;
		if (tok->type != TOKEN_WORD && tok->type != TOKEN_PIPE)
		{
			args = ft_calloc(2, sizeof(char *));
			if (curr->next)
				args[0] = ft_strdup(((t_token *)curr->next->content)->value);
			redir_node = create_node(tok->type, args, cmd_node, NULL);
			cmd_node = redir_node;
			curr = curr->next;
		}
		if (curr)
			curr = curr->next;
	}
	return (cmd_node);
}

static t_nodes	*create_cmd_node(t_nodes *tokens)
{
	t_nodes	*cmd_node;
	char	**args;
	t_nodes	*curr;
	int		count;
	int		i;

	count = 0;
	curr = tokens;
	while (curr)
	{
		if (((t_token *)curr->content)->type == TOKEN_WORD)
			count++;
		else if (((t_token *)curr->content)->type != TOKEN_PIPE)
			if (curr->next) curr = curr->next; 
		curr = curr->next;
	}
	args = ft_calloc(count + 1, sizeof(char *));
	i = 0;
	curr = tokens;
	while (curr)
	{
		if (((t_token *)curr->content)->type == TOKEN_WORD)
			args[i++] = ft_strdup(((t_token *)curr->content)->value);
		else if (((t_token *)curr->content)->type != TOKEN_PIPE)
			if (curr->next) curr = curr->next;
		curr = curr->next;
	}
	cmd_node = create_node(TOKEN_WORD, args, NULL, NULL);
	return (process_redirections(cmd_node, tokens));
}

t_nodes	*ast_builder(t_nodes *tokens)
{
	t_nodes	*cursor;
	t_nodes	*prev;
	t_token	*tok;
	t_ast	*pipe_data;

	if (!tokens)
		return (NULL);
	cursor = tokens;
	prev = NULL;
	while (cursor)
	{
		tok = (t_token *)cursor->content;
		if (tok->type == TOKEN_PIPE)
		{
			if (prev)
				prev->next = NULL;
			else
				tokens = NULL;
			pipe_data = ft_calloc(1, sizeof(t_ast));
			if (!pipe_data) return (NULL); 
			pipe_data->type = TOKEN_PIPE;
			pipe_data->left = ast_builder(tokens);
			pipe_data->right = ast_builder(cursor->next);
			return (ft_lstnew(pipe_data));
		}
		prev = cursor;
		cursor = cursor->next;
	}
	return (create_cmd_node(tokens));
}
