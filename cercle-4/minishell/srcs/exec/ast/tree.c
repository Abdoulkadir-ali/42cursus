/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:42:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:15:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Dispatch an AST node to the executor matching its token type.
 * @param ast_node Node selected from the parsed command tree.
 * @param state Active shell state shared across recursive execution.
 * @return Exit status produced by the executed node.
 */
int	exec_tree(t_ast *ast_node, t_shell_state *state)
{
	if (!ast_node)
		return (0);
	if (ast_node->type == TOKEN_WORD)
		return (exec_simple_command(ast_node, state));
	else if (ast_node->type == TOKEN_PIPE)
		return (exec_pipe(ast_node, state));
	else if (ast_node->type == TOKEN_RED_IN || ast_node->type == TOKEN_RED_OUT
		|| ast_node->type == TOKEN_APPEND
		|| ast_node->type == TOKEN_HEREDOC)
		return (exec_redirection(ast_node, state));
	else if (ast_node->type == TOKEN_AND)
		return (exec_logical(ast_node, state, 1));
	else if (ast_node->type == TOKEN_OR)
		return (exec_logical(ast_node, state, 0));
	else if (ast_node->type == TOKEN_SUBSHELL)
		return (exec_subshell(ast_node, state));
	else if (ast_node->type == TOKEN_SEMICOLON)
	{
		exec_tree(ast_node->left, state);
		return (exec_tree(ast_node->right, state));
	}
	return (0);
}
