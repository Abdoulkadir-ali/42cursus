/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:42:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:57:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_tree(t_ast *ast_node, t_shell_state *state)
{
	t_ast	*node;

	if (!ast_node)
		return (0);
	node = ast_node;
	if (node->type == TOKEN_WORD)
		return (exec_simple_command(node, state));
	else if (node->type == TOKEN_PIPE)
		return (exec_pipe(node, state));
	else if (node->type == TOKEN_RED_IN || node->type == TOKEN_RED_OUT
		|| node->type == TOKEN_APPEND || node->type == TOKEN_HEREDOC)
		return (exec_redirection(node, state));
	else if (node->type == TOKEN_AND)
		return (exec_logical(node, state, 1));
	else if (node->type == TOKEN_OR)
		return (exec_logical(node, state, 0));
	else if (node->type == TOKEN_SUBSHELL)
		return (exec_subshell(node, state));
	else if (node->type == TOKEN_SEMICOLON)
	{
		exec_tree(node->left, state);
		return (exec_tree(node->right, state));
	}
	return (0);
}
