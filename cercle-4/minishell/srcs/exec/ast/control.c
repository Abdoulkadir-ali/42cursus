/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:20:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/21 06:52:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_subshell(t_ast *node, char ***envp)
{
	pid_t	pid;
	int		status;
	int		dbg_fd;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		g_state.interactive_shell = 0;
		dbg_fd = open("/tmp/minishell_dbg.log", O_WRONLY | O_CREAT | O_APPEND,
				0600);
		if (dbg_fd != -1)
		{
			dprintf(dbg_fd, "[exec_subshell child start] pid=%d\n", getpid());
			close(dbg_fd);
		}
		status = exec_tree(node->left, envp);
		dbg_fd = open("/tmp/minishell_dbg.log", O_WRONLY | O_CREAT | O_APPEND,
				0600);
		if (dbg_fd != -1)
		{
			dprintf(dbg_fd, "[exec_subshell child exit] pid=%d ret=%d\n",
				getpid(), status);
			close(dbg_fd);
		}
		exit(status);
	}
	setup_signals(SIGNAL_BLOCKING);
	waitpid(pid, &status, 0);
	dbg_fd = open("/tmp/minishell_dbg.log", O_WRONLY | O_CREAT | O_APPEND,
			0600);
	if (dbg_fd != -1)
	{
		dprintf(dbg_fd,
			"[exec_subshell parent waited] pid=%d child=%d status=%d\n",
			getpid(), pid, status);
		close(dbg_fd);
	}
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
