/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:20:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/13 23:45:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_simple_command(t_ast *node, char ***envp)
{
	pid_t	pid;
	char	*path;

	if (is_builtin(node->args[0], node->args))
		return (exec_builtin(node->args, envp));
	else
	{
		path = find_path(node->args[0], (char **) *envp);
		if (!path)
			return (127);
		pid = fork();
		if (pid == 0)
		{
			execve(path, node->args, *envp);
			exit(1);
		}
		waitpid(pid, NULL, 0);
		free(path);
		return (0);
	}
}
