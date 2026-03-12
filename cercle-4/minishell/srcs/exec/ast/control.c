/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:15:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Execute a subshell branch inside the forked child.
 * @param node Subshell AST node whose left branch must run.
 * @param state Active shell state passed to the executor.
 * @return This function does not return. It exits with the branch status.
 */
static void	exec_subshell_child(t_ast *node, t_shell_state *state)
{
	int		status;

	signal(SIGQUIT, SIG_DFL);
	state->interactive_shell = 0;
	status = exec_tree(node->left, state);
	exit(status);
}

/**
 * @brief Wait for a subshell child and normalize its termination status.
 * @param pid Process identifier returned by fork for the subshell.
 * @return Shell-compatible exit status for the child process.
 */
static int	exec_subshell_parent(pid_t pid)
{
	int		status;

	setup_signals(SIGNAL_BLOCKING);
	waitpid(pid, &status, 0);
	setup_signals(SIGNAL_INTERACTIVE);
	return (handle_wait_status(status));
}

/**
 * @brief Execute a subshell AST node in an isolated process.
 * @param node AST node describing the subshell command group.
 * @param state Active shell state shared by the executor.
 * @return Exit status produced by the subshell execution.
 */
int	exec_subshell(t_ast *node, t_shell_state *state)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_subshell_child(node, state);
	else
		return (exec_subshell_parent(pid));
	return (0);
}

/**
 * @brief Execute a logical operator node with shell short-circuit rules.
 * @param node AST node containing left and right command branches.
 * @param state Active shell state passed through recursive execution.
 * @param run_if_zero True for && semantics, false for || semantics.
 * @return Status of the last branch that was evaluated.
 */
int	exec_logical(t_ast *node, t_shell_state *state, bool run_if_zero)
{
	int	left;

	left = exec_tree(node->left, state);
	if ((run_if_zero && left == 0) || (!run_if_zero && left != 0))
		return (exec_tree(node->right, state));
	return (left);
}
