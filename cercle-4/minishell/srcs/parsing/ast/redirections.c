/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/03/09 23:59:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Collect redirection tokens into a stack processed from right to left.
 * @param stack Output stack of redirection token nodes.
 * @param tokens Token list being scanned for redirections.
 * @return This function does not return a value.
 */
static void	push_to_stack(t_nodes **stack, t_nodes *tokens)
{
	t_nodes	*curr;
	t_token	*tok;

	curr = tokens;
	while (curr)
	{
		tok = (t_token *)curr->content;
		if (!tok->expanded && tok->type != TOKEN_WORD
			&& tok->type != TOKEN_PIPE)
		{
			ft_lstadd_front(stack, ft_lstnew(curr));
			if (curr->next)
				curr = curr->next;
		}
		if (curr)
			curr = curr->next;
	}
}

/**
 * @brief Build the argv-like payload stored on one redirection AST node.
 * @param tok Redirection token that defines the node type.
 * @param redir_token_node Token-list node pointing at the redirection token.
 * @return Newly allocated redirection argument array.
 */
static char	**build_redir_args(t_token *tok, t_nodes *redir_token_node)
{
	char	**args;
	t_token	*delim_tok;
	int		fd_len;

	args = ft_calloc(3, sizeof(char *));
	if (redir_token_node->next)
	{
		delim_tok = (t_token *)redir_token_node->next->content;
		args[0] = ft_strdup(delim_tok->value);
		if (tok->type == TOKEN_HEREDOC || tok->type == TOKEN_HERESTR)
			args[1] = ft_itoa(delim_tok->quoted);
		else
		{
			fd_len = 0;
			while (ft_isdigit(tok->value[fd_len]))
				fd_len++;
			if (fd_len > 0)
				args[1] = ft_substr(tok->value, 0, fd_len);
		}
	}
	else
		args[0] = ft_strdup("");
	return (args);
}

/**
 * @brief Wrap the current command AST with one redirection AST node.
 * @param cmd_node Address of the current command subtree root.
 * @param redir_token_node Token-list node pointing at the redirection token.
 * @return This function does not return a value.
 */
static void	apply_redir(t_ast **cmd_node, t_nodes *redir_token_node)
{
	t_token	*tok;
	char	**args;
	t_ast	*redir_node;

	tok = (t_token *)redir_token_node->content;
	args = build_redir_args(tok, redir_token_node);
	redir_node = create_node(tok->type, args, *cmd_node, NULL);
	*cmd_node = redir_node;
}

/**
 * @brief Wrap a command or subshell AST with every redirection in the tokens.
 * @param cmd_node Existing command subtree to be wrapped.
 * @param tokens Token list scanned for redirections.
 * @return Root AST node after all redirections have been applied.
 */
t_ast	*process_redirections(t_ast *cmd_node, t_nodes *tokens)
{
	t_nodes	*stack;
	t_nodes	*s_curr;

	stack = NULL;
	push_to_stack(&stack, tokens);
	s_curr = stack;
	while (s_curr)
	{
		apply_redir(&cmd_node, (t_nodes *)s_curr->content);
		s_curr = s_curr->next;
	}
	ft_lstclear(&stack, NULL);
	return (cmd_node);
}
