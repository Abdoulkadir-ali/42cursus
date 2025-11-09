/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:44:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 16:38:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	init_pipes(int nb_cmds, t_pipe **pipes)
{
	if (nb_cmds > 1)
	{
		*pipes = create_pipes(nb_cmds);
		if (!*pipes)
			return (exit_statement("pipes", NULL, -1));
	}
	return (0);
}

static int	fork_processes(t_config *cfg, t_pipe *pipes)
{
	int	i;
	int	pid;
	int	last_pid;

	i = 0;
	last_pid = 0;
	while (i < cfg->nb_cmds)
	{
		pid = fork();
		if (pid < 0)
			exit_statement("fork", pipes, -1);
		if (!pid)
			run_process(cfg, i, pipes);
		if (i == cfg->nb_cmds - 1)
			last_pid = pid;
		i++;
	}
	return (last_pid);
}

static int	wait_children(int nb_cmds, int last_pid)
{
	int	status;
	int	exit_code;
	int	i;
	int	pid;

	exit_code = 0;
	i = 0;
	while (i < nb_cmds)
	{
		pid = wait(&status);
		if (pid == -1)
			return (1);
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status) && WTERMSIG(status) != SIGPIPE)
				exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (exit_code);
}

static void	cleanup(t_pipe *pipes)
{
	if (pipes)
		free(pipes);
}

int	pipex(char **argv, int argc, int append_mode)
{
	t_config	cfg;
	t_pipe		*pipes;
	int			exit_code;
	int			last_pid;

	cfg.argv = argv;
	cfg.nb_cmds = argc - 2;
	cfg.append_mode = append_mode;
	pipes = NULL;
	if (init_pipes(cfg.nb_cmds, &pipes) == -1)
		return (1);
	last_pid = fork_processes(&cfg, pipes);
	if (cfg.nb_cmds > 1)
		close_all_pipes(pipes, cfg.nb_cmds - 1);
	exit_code = wait_children(cfg.nb_cmds, last_pid);
	cleanup(pipes);
	return (exit_code);
}
