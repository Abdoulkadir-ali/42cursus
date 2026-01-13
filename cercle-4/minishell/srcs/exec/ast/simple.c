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

static int	path_is_set(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	child_execution(char *path, t_ast *node, char ***envp)
{
	struct stat	st;

	signal(SIGQUIT, SIG_DFL);
	ft_set_env("_", path, envp);
	execve(path, node->args, *envp);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(node->args[0], 2);
	if (errno == ENOENT)
	{
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);
	}
	if (errno == EACCES)
	{
		if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
			ft_putendl_fd(": Is a directory", 2);
		else
			ft_putendl_fd(": Permission denied", 2);
		exit(126);
	}
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	exit(1);
}

static int	run_external_command(char *path, t_ast *node, char ***envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		child_execution(path, node, envp);
	setup_signals(SIGNAL_BLOCKING);
	waitpid(pid, &status, 0);
	setup_signals(SIGNAL_INTERACTIVE);
	free(path);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	exec_simple_command(t_ast *node, char ***envp)
{
	char		*path;

	if (!node->args || !node->args[0])
		return (0);
	if (is_builtin(node->args[0], node->args))
		return (exec_builtin(node->args, envp));
	path = find_path(node->args[0], *envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->args[0], 2);
		if (path_is_set(*envp))
			ft_putendl_fd(": command not found", 2);
		else
			ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	return (run_external_command(path, node, envp));
}
