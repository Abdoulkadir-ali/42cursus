/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 05:27:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	child_left(t_ast *node, int *p_fd, char ***envp)
{
	close(p_fd[0]);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	exit(exec_tree(node->left, envp));
}

static void	child_right(t_ast *node, int *p_fd, char ***envp)
{
	close(p_fd[1]);
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[0]);
	exit(exec_tree(node->right, envp));
}

int	exec_pipe(t_ast *node, char ***envp)
{
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(p_fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == 0)
		child_left(node, p_fd, envp);
	pid2 = fork();
	if (pid2 == 0)
		child_right(node, p_fd, envp);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
