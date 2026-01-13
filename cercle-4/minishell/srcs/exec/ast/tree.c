/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:42:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 23:44:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_tree(t_nodes *ast_node, char ***envp)
{
	t_ast	*node;

	if (!ast_node)
		return (0);
	node = (t_ast *)ast_node->content;
	if (node->type == TOKEN_WORD)
		return (exec_simple_command(node, envp));
	else if (node->type == TOKEN_PIPE)
		return (exec_pipe(node, envp));
	else if (node->type == TOKEN_RED_IN || node->type == TOKEN_RED_OUT
		|| node->type == TOKEN_APPEND || node->type == TOKEN_HEREDOC)
		return (exec_redirection(node, envp));
	else if (node->type == TOKEN_AND)
		return (exec_logical_and(node, envp));
	else if (node->type == TOKEN_OR)
		return (exec_logical_or(node, envp));
	else if (node->type == TOKEN_SUBSHELL)
		return (exec_subshell(node, envp));
	return (0);
}
