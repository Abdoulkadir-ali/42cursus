/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:05:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/01/26 00:41:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_cmd_args(t_nodes *tokens)
{
	t_nodes	*curr;
	int		count;

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
	return (count);
}

static void	fill_cmd_args(t_nodes *tokens, char **args)
{
	t_nodes	*curr;
	int		i;

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
}

static void	set_cmd_quoted_state(t_nodes *node, t_nodes *tokens)
{
	t_nodes	*curr;
	t_ast	*ast;
	t_token	*tok;

	ast = (t_ast *)node->content;
	curr = tokens;
	while (curr)
	{
		tok = (t_token *)curr->content;
		if (tok->type == TOKEN_WORD)
		{
			ast->is_quoted = tok->quoted;
			break ;
		}
		curr = curr->next;
	}
}

static t_nodes	*handle_simple_cmd(t_nodes *tokens)
{
	char	**args;
	int		count;
	t_nodes	*node;

	count = count_cmd_args(tokens);
	args = ft_calloc(count + 1, sizeof(char *));
	fill_cmd_args(tokens, args);
	node = create_node(TOKEN_WORD, args, NULL, NULL);
	set_cmd_quoted_state(node, tokens);
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
