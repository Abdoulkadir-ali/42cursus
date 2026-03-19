/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:14:13 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/19 05:08:14 by abdoali          ###   ########.fr       */
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
	if (cmp_ast_type(ast_node, TOKEN_WORD))
		return (exec_simple_command(ast_node, state));
	else if (cmp_ast_type(ast_node, TOKEN_PIPE))
		return (exec_pipe(ast_node, state));
	else if (cmp_ast_type(ast_node, TOKEN_RED_IN) || cmp_ast_type(ast_node,
			TOKEN_RED_OUT) || cmp_ast_type(ast_node, TOKEN_APPEND)
		|| cmp_ast_type(ast_node, TOKEN_HEREDOC))
		return (exec_redirection(ast_node, state));
	else if (cmp_ast_type(ast_node, TOKEN_AND))
		return (exec_logical(ast_node, state, 1));
	else if (cmp_ast_type(ast_node, TOKEN_OR))
		return (exec_logical(ast_node, state, 0));
	else if (cmp_ast_type(ast_node, TOKEN_SUBSHELL))
		return (exec_subshell(ast_node, state));
	else if (cmp_ast_type(ast_node, TOKEN_BACKGROUND))
		return (exec_task(ast_node, state));
	else if (cmp_ast_type(ast_node, TOKEN_SEMICOLON))
	{
		exec_tree(ast_node->left, state);
		return (exec_tree(ast_node->right, state));
	}
	return (0);
}
