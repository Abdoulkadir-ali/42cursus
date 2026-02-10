/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:59:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/09 04:14:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
