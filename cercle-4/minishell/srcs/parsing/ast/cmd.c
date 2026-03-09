/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:05:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/03/09 23:59:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Count positional command arguments while skipping redirection payloads.
 * @param tokens Token list representing one simple command region.
 * @return Number of `TOKEN_WORD` arguments belonging to the command.
 */
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

/**
 * @brief Copy command arguments into the argv array stored on the AST node.
 * @param tokens Token list representing one simple command region.
 * @param args Destination argv array already sized for all command words.
 * @return This function does not return a value.
 */
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

/**
 * @brief Copy the quote state of the first command word into the AST node.
 * @param node AST node describing the simple command.
 * @param tokens Token list used to locate the first command word.
 * @return This function does not return a value.
 */
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

/**
 * @brief Build a simple-command AST node and wrap its redirections.
 * @param tokens Token list representing one simple command.
 * @return Root AST node for the command or its redirection chain.
 */
static t_ast	*handle_simple_cmd(t_nodes *tokens)
{
	char	**args;
	int		count;
	t_ast	*node;

	node = NULL;
	count = count_cmd_args(tokens);
	if (count == 0)
	{
		node = process_redirections(NULL, tokens);
		ft_lstclear(&tokens, del_token);
		return (node);
	}
	args = ft_calloc(count + 1, sizeof(char *));
	fill_cmd_args(tokens, args);
	node = create_node(TOKEN_WORD, args, NULL, NULL);
	set_cmd_quoted_state(node, tokens);
	node = process_redirections(node, tokens);
	ft_lstclear(&tokens, del_token);
	return (node);
}

/**
 * @brief Select whether a token list becomes a command node or subshell node.
 * @param tokens Token list representing one AST leaf region.
 * @return Root AST node for the parsed command or subshell.
 */
t_ast	*create_cmd_node(t_nodes *tokens)
{
	t_nodes	*curr;

	curr = tokens;
	if (curr && ((t_token *)curr->content)->type == TOKEN_LPAREN)
		return (handle_subshell(tokens));
	return (handle_simple_cmd(tokens));
}
