/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/09 04:12:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

static void	apply_redir(t_ast **cmd_node, t_nodes *redir_token_node)
{
	t_token	*tok;
	char	**args;
	t_ast	*redir_node;

	tok = (t_token *)redir_token_node->content;
	args = ft_calloc(3, sizeof(char *));
	if (redir_token_node->next)
	{
		t_token *delim_tok = (t_token *)redir_token_node->next->content;
		args[0] = ft_strdup(delim_tok->value);
		if (tok->type == TOKEN_HEREDOC || tok->type == TOKEN_HERESTR)
			args[1] = ft_itoa(delim_tok->quoted);
	}
	else
		args[0] = ft_strdup("");
	redir_node = create_node(tok->type, args, *cmd_node, NULL);
	*cmd_node = redir_node;
}

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
