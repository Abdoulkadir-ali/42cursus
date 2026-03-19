/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 03:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Report a command not found error or path resolution error.
 * @param cmd Command string that failed to execute.
 * @param state Active shell state used to access environment.
 * @return 127 as specified by shell standards.
 */
int	report_command_not_found(char *cmd, t_shell_state *state)
{
	if (!cmd)
		return (127);
	if (ft_strchr(cmd, '/') || !ft_get_env("PATH", state->envp))
		ft_puterror("%s: No such file or directory\n", cmd);
	else
		ft_puterror("%s: command not found\n", cmd);
	return (127);
}

/**
 * @brief Report a fatal fork() error using standard error.
 * @return Always returns 1.
 */
int	report_fork_error(void)
{
	ft_puterror("fork: %s\n", strerror(errno));
	return (1);
}

/**
 * @brief Print quit/core dump diagnostic to standard error.
 */
void	report_quit_core_dump(void)
{
	ft_puterror("Quit (core dumped)\n");
}

/**
 * @brief Wrap fork() with automated error reporting for resource exhaustion.
 * @return The PID resulting from the fork call.
 */
pid_t	fork_protected(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_puterror("fork: %s\n", strerror(errno));
	return (pid);
}

/**
 * @brief Create a pipe with error handling on failure.
 * @param pipefd Array where file descriptors will be stored.
 * @return 0 on success, or 1 on error.
 */
int	pipe_protected(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		ft_puterror("pipe: %s\n", strerror(errno));
		return (1);
	}
	return (0);
}
