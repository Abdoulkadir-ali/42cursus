/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:59:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/12 01:48:55 by abdoali          ###   ########.fr       */
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
	t_nodes	*stack;
	t_nodes	*s_curr;
	t_nodes	*redir_token_node;
	char	**args;
	t_nodes	*redir_node;

	stack = NULL;
	curr = tokens;
	while (curr)
	{
		tok = (t_token *)curr->content;
			if (tok->expanded == 0 && tok->type != TOKEN_WORD && tok->type != TOKEN_PIPE)
		{
			ft_lstadd_front(&stack, ft_lstnew(curr));
			if (curr->next)
				curr = curr->next;
		}
		if (curr)
			curr = curr->next;
	}
	s_curr = stack;
	while (s_curr)
	{
		redir_token_node = (t_nodes *)s_curr->content;
		tok = (t_token *)redir_token_node->content;
		args = ft_calloc(3, sizeof(char *));
		if (redir_token_node->next)
		{
			/* Preserve the exact token value (including original quote characters)
			   The heredoc code will inspect/remove quotes and decide whether to expand. */
			args[0] = ft_strdup(((t_token *)redir_token_node->next->content)->value);
		}
		else
		{
			// Safe fallback or error indication. 
			// If we are here, syntax check passed but argument vanished (empty var).
			// Bash treats `<< $EMPTY` as syntax error.
			// We can mimic this by setting args[0] to empty string?
			// Or leave it NULL? exec_redirection handles NULL?
			args[0] = ft_strdup(""); 
		}
		args[1] = ft_strdup(tok->value);
		redir_node = create_node(tok->type, args, cmd_node, NULL);
		cmd_node = redir_node;
		s_curr = s_curr->next;
	}
	ft_lstclear(&stack, NULL);
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
	cmd_node = process_redirections(cmd_node, tokens);
	ft_lstclear(&tokens, del_token);
	return (cmd_node);
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
		if (tok->type == TOKEN_PIPE || tok->type == TOKEN_SEMICOLON)
		{
			if (prev)
				prev->next = NULL;
			else
				tokens = NULL;
			pipe_data = ft_calloc(1, sizeof(t_ast));
			if (!pipe_data) return (NULL); 
			pipe_data->type = tok->type;
			pipe_data->left = ast_builder(tokens);
			pipe_data->right = ast_builder(cursor->next);
			del_token(cursor->content);
			free(cursor);
			return (ft_lstnew(pipe_data));
		}
		prev = cursor;
		cursor = cursor->next;
	}
	return (create_cmd_node(tokens));
}
