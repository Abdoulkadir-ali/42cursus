/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:20:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/14 17:52:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_subshell(t_ast *node, char ***envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		g_state.interactive_shell = 0;
		exit(exec_tree(node->left, envp));
	}
	setup_signals(SIGNAL_BLOCKING);
	waitpid(pid, &status, 0);
	setup_signals(SIGNAL_INTERACTIVE);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_puterror("Quit (core dumped)\n");
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	exec_logical_or(t_ast *node, char ***envp)
{
	int	left_status;

	left_status = exec_tree(node->left, envp);
	if (left_status != 0)
		return (exec_tree(node->right, envp));
	return (left_status);
}

int	exec_logical_and(t_ast *node, char ***envp)
{
	int	left_status;

	left_status = exec_tree(node->left, envp);
	if (left_status == 0)
		return (exec_tree(node->right, envp));
	return (left_status);
}
