/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 13:34:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	exec_subshell_child(t_ast *node, t_shell_state *state)
{
	int		status;
	int		dbg_fd;

	signal(SIGQUIT, SIG_DFL);
	state->interactive_shell = 0;
	dbg_fd = open("/tmp/minishell_dbg.log", O_WRONLY | O_CREAT | O_APPEND,
			0600);
	if (dbg_fd != -1)
	{
		dprintf(dbg_fd, "[exec_subshell child start] pid=%d\n", getpid());
		close(dbg_fd);
	}
	status = exec_tree(node->left, state);
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
	int		dbg_fd;

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
