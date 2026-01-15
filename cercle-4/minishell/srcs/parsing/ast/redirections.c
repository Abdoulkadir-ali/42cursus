/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 00:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/01/15 04:43:29 by abdoali          ###   ########.fr       */
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

static void	apply_redir(t_nodes **cmd_node, t_nodes *redir_token_node)
{
	t_token	*tok;
	char	**args;
	t_nodes	*redir_node;

	tok = (t_token *)redir_token_node->content;
	args = ft_calloc(3, sizeof(char *));
	if (redir_token_node->next)
		args[0] = ft_strdup(((t_token *)redir_token_node->next->content)->value);
	else
		args[0] = ft_strdup("");
	args[1] = ft_strdup(tok->value);
	redir_node = create_node(tok->type, args, *cmd_node, NULL);
	*cmd_node = redir_node;
}

t_nodes	*process_redirections(t_nodes *cmd_node, t_nodes *tokens)
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
