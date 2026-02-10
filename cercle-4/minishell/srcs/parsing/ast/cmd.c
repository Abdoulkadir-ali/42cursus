/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:05:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/09 04:12:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_cmd_args(t_nodes *tokens)
{
	t_nodes	*curr;
	int		count;

	count = 0;
	curr = tokens;
	while (curr && ((t_token *)curr->content)->type != TOKEN_PIPE)
	{
		if (((t_token *)curr->content)->type == TOKEN_WORD)
			count++;
		else if (is_redirection(((t_token *)curr->content)->type) && curr->next)
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
	while (curr && ((t_token *)curr->content)->type != TOKEN_PIPE)
	{
		if (((t_token *)curr->content)->type == TOKEN_WORD)
		{
			if (args)
				args[i++] = ft_strdup(((t_token *)curr->content)->value);
		}
		else if (is_redirection(((t_token *)curr->content)->type) && curr->next)
			curr = curr->next;
		curr = curr->next;
	}
	if (args)
		args[i] = NULL;
}

static void	set_cmd_quoted_state(t_ast *node, t_nodes *tokens)
{
	t_nodes	*curr;
	t_token	*tok;

	if (!node || !tokens)
		return ;
	curr = tokens;
	while (curr && ((t_token *)curr->content)->type != TOKEN_PIPE)
	{
		tok = (t_token *)curr->content;
		if (!tok)
			break ;
		if (tok->type == TOKEN_WORD)
		{
			node->is_quoted = tok->quoted;
			break ;
		}
		else if (is_redirection(tok->type) && curr->next)
			curr = curr->next;
		curr = curr->next;
	}
}

static t_ast	*handle_simple_cmd(t_nodes *tokens)
{
	char	**args;
	int		count;
	t_ast	*node;

	node = NULL;
	count = count_cmd_args(tokens);
	if (count == 0)
	{
		process_redirections(NULL, tokens);
		ft_lstclear(&tokens, del_token);
		return (NULL);
	}
	args = ft_calloc(count + 1, sizeof(char *));
	fill_cmd_args(tokens, args);
	node = create_node(TOKEN_WORD, args, NULL, NULL);
	set_cmd_quoted_state(node, tokens);
	node = process_redirections(node, tokens);
	ft_lstclear(&tokens, del_token);
	return (node);
}

t_ast	*create_cmd_node(t_nodes *tokens)
{
	t_nodes	*curr;

	curr = tokens;
	if (curr && ((t_token *)curr->content)->type == TOKEN_LPAREN)
		return (handle_subshell(tokens));
	return (handle_simple_cmd(tokens));
}
