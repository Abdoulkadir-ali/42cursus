/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 04:13:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	exec_subshell_child(t_ast *node, t_shell_state *state)
{
	int		status;

	signal(SIGQUIT, SIG_DFL);
	state->interactive_shell = 0;
	status = exec_tree(node->left, state);
	exit(status);
}

static int	exec_subshell_parent(pid_t pid)
{
	int		status;

	setup_signals(SIGNAL_BLOCKING);
	waitpid(pid, &status, 0);
	setup_signals(SIGNAL_INTERACTIVE);
	return (handle_wait_status(status));
}

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

int	exec_logical(t_ast *node, t_shell_state *state, int run_if_zero)
{
	int	left;

	left = exec_tree(node->left, state);
	if ((run_if_zero && left == 0) || (!run_if_zero && left != 0))
		return (exec_tree(node->right, state));
	return (left);
}
