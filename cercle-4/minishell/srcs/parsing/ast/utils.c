/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:59:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:16:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_nodes	*create_node(t_token_type type, char **args, t_nodes *left,
		t_nodes *right)
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
	return (ft_lstnew(ast));
}

void	dump_tokens_list(t_nodes *head, const char *stage)
{
	FILE	*f;
	t_nodes	*cur;
	t_token	*tok;

	f = fopen("log/expand_debug.txt", "a");
	if (!f)
		return ;
	fprintf(f, "-- %s --\n", stage);
	cur = head;
	while (cur)
	{
		tok = (t_token *)cur->content;
		if (tok && tok->value)
			fprintf(f, "type=%d quoted=%d expanded=%d val='%s'\n", tok->type,
				tok->quoted, tok->expanded, tok->value);
		else
			fprintf(f, "<null token>\n");
		cur = cur->next;
	}
	fprintf(f, "-- end %s --\n\n", stage);
	fclose(f);
}

void	free_ast_node(t_nodes *ast_node)
{
	t_ast	*ast;
	int		i;

	if (!ast_node)
		return ;
	ast = (t_ast *)ast_node->content;
	if (ast->left)
		free_ast_node(ast->left);
	if (ast->right)
		free_ast_node(ast->right);
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

void	append_chunk_safe(char **res, char *chunk)
{
	char	*tmp;

	if (!chunk)
		return ;
	if (!*res)
		*res = chunk;
	else
	{
		tmp = ft_strjoin(*res, chunk);
		free(*res);
		free(chunk);
		*res = tmp;
	}
}

void	add_token_node(t_nodes **head, t_nodes **tail, char *val, int quoted)
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

void	print_ast(t_nodes *ast_node, int depth)
{
	int		i;
	t_ast	*node;

	if (!ast_node)
		return ;
	node = (t_ast *)ast_node->content;
	i = 0;
	while (i < depth)
	{
		ft_printf("  ");
		i++;
	}
	if (node->type == TOKEN_PIPE)
	{
		ft_printf("PIPE\n");
		print_ast(node->left, depth + 1);
		print_ast(node->right, depth + 1);
	}
	else if (node->type == TOKEN_WORD)
	{
		ft_printf("CMD: ");
		i = 0;
		while (node->args && node->args[i])
		{
			ft_printf("[%s] ", node->args[i]);
			i++;
		}
		ft_printf("\n");
	}
}
