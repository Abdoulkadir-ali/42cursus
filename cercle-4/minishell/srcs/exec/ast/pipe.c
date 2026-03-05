/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:20:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:20:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static pid_t	fork_left_command(int pipefd[2], t_ast *node,
		t_shell_state *state)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(exec_tree(node->left, state));
	}
	return (pid);
}

static pid_t	fork_right_command(int pipefd[2], t_ast *node,
		t_shell_state *state)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(exec_tree(node->right, state));
	}
	return (pid);
}

static int	wait_for_children(pid_t pid1, pid_t pid2)
{
	int	status;

	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (handle_wait_status(status));
}

int	exec_pipe(t_ast *node, t_shell_state *state)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
		return (1);
	pid1 = fork_left_command(pipefd, node, state);
	if (pid1 == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (1);
	}
	pid2 = fork_right_command(pipefd, node, state);
	if (pid2 == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return (wait_for_children(pid1, pid2));
}
