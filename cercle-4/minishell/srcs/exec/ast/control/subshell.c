/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 23:41:38 by abdoali          ###   ########.fr       */
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

static int	handle_subshell_status(int status)
{
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

static int	exec_subshell_parent(pid_t pid)
{
	int		status;

	setup_signals(SIGNAL_BLOCKING);
	waitpid(pid, &status, 0);
	setup_signals(SIGNAL_INTERACTIVE);
	return (handle_subshell_status(status));
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
