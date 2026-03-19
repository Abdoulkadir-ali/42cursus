/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbranco <hbranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:14:02 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/18 02:14:04 by hbranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Fork the left pipeline child and connect it to the write end.
 * @param pipefd Pipe descriptors shared by both pipeline children.
 * @param node Pipeline AST node whose left branch is executed.
 * @param state Active shell state passed to recursive execution.
 * @return Child pid in the parent, or zero inside the child before exit.
 */
static pid_t	fork_left_command(int pipefd[2], t_ast *node,
		t_shell_state *state)
{
	pid_t	pid;

	pid = fork_protected();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_child_signals();
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(exec_tree(node->left, state));
	}
	return (pid);
}

/**
 * @brief Fork the right pipeline child and connect it to the read end.
 * @param pipefd Pipe descriptors shared by both pipeline children.
 * @param node Pipeline AST node whose right branch is executed.
 * @param state Active shell state passed to recursive execution.
 * @return Child pid in the parent, or zero inside the child before exit.
 */
static pid_t	fork_right_command(int pipefd[2], t_ast *node,
		t_shell_state *state)
{
	pid_t	pid;

	pid = fork_protected();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_child_signals();
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(exec_tree(node->right, state));
	}
	return (pid);
}

/**
 * @brief Wait for both children of a pipeline and report the right status.
 * @param pid1 Left-side child process identifier.
 * @param pid2 Right-side child process identifier.
 * @return Shell-compatible status for the rightmost pipeline command.
 */
static int	wait_for_children(pid_t pid1, pid_t pid2)
{
	int	status;

	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (handle_wait_status(status));
}

/**
 * @brief Execute a pipeline AST node by forking its two branches.
 * @param node Pipeline AST node with left and right commands.
 * @param state Active shell state passed to recursive execution.
 * @return Exit status reported for the pipeline.
 */
int	exec_pipe(t_ast *node, t_shell_state *state)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe_protected(pipefd))
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
