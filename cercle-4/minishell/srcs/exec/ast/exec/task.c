/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 03:04:27 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 05:07:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Execute a background task: fork, run left branch in child and
 * continue with right branch in the parent without waiting.
 * @param ast_node AST node whose left is the background job and right is the
 * next command to run.
 * @param state Shell state passed to executed branches.
 * @return Exit status of the right branch or 1 on fork failure.
 */
int	exec_task(t_ast *ast_node, t_shell_state *state)
{
	pid_t	pid;

	if (!ast_node)
		return (0);
	pid = fork_protected();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		setup_child_signals();
		(void)setpgid(0, 0);
		_exit(exec_tree(ast_node->left, state));
	}
	return (exec_tree(ast_node->right, state));
}
