/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:20:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/26 04:30:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	path_is_set(t_shell_state *state)
{
	int	i;

	i = 0;
	while (state->envp && state->envp[i])
	{
		if (ft_strncmp(state->envp[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	child_execution(char *path, t_ast *node, t_shell_state *state)
{
	struct stat	st;

	signal(SIGQUIT, SIG_DFL);
	ft_set_env("_", path, state);
	execve(path, node->args, state->envp);
	if (errno == ENOENT)
	{
		ft_puterror("%s: No such file or directory\n", node->args[0]);
		exit(127);
	}
	if (errno == EACCES)
	{
		if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
			ft_puterror("%s: Is a directory\n", node->args[0]);
		else
			ft_puterror("%s: Permission denied\n", node->args[0]);
		exit(126);
	}
	ft_puterror("%s: ", node->args[0]);
	perror(NULL);
	exit(1);
}

static int	run_external_command(char *path, t_ast *node, t_shell_state *state)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		child_execution(path, node, state);
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
			ft_puterror("Quit (core dumped)\n");
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	exec_simple_command(t_ast *node, t_shell_state *state)
{
	char		*path;

	if (!node->args || !node->args[0])
		return (0);
	if (is_builtin(node->args[0], node->args, node->is_quoted))
		return (exec_builtin(node->args, state));
	path = find_path(node->args[0], state);
	if (!path)
	{
		if (path_is_set(state))
			ft_puterror("%s: command not found\n", node->args[0]);
		else
			ft_puterror("%s: No such file or directory\n", node->args[0]);
		return (127);
	}
	return (run_external_command(path, node, state));
}
