/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:11:33 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 21:43:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_output_file(t_config *cfg, int i, t_pipe *pipes)
{
	if (cfg->append_mode)
		write_to_outfile_append(cfg->argv[cfg->nb_cmds + 1], pipes, i,
			cfg->nb_cmds);
	else
		write_to_outfile(cfg->argv[cfg->nb_cmds + 1], pipes, i, cfg->nb_cmds);
}

static void	setup_single_cmd(t_config *cfg, int i, t_pipe *pipes)
{
	read_from_infile(cfg->argv[0], pipes, cfg->nb_cmds);
	handle_output_file(cfg, i, pipes);
}

static void	setup_process_io(t_config *cfg, int i, t_pipe *pipes)
{
	if (i == 0 && i == cfg->nb_cmds - 1)
		setup_single_cmd(cfg, i, pipes);
	else if (i == 0)
		read_from_infile(cfg->argv[0], pipes, cfg->nb_cmds);
	else if (i == cfg->nb_cmds - 1)
		handle_output_file(cfg, i, pipes);
	else
	{
		dup2(pipes[i - 1][READ_END], STDIN_FILENO);
		dup2(pipes[i][WRITE_END], STDOUT_FILENO);
	}
}

int	run_process(t_config *cfg, int i, t_pipe *pipes)
{
	setup_process_io(cfg, i, pipes);
	if (cfg->nb_cmds > 1)
	{
		close_all_pipes(pipes, cfg->nb_cmds - 1);
		free(pipes);
	}
	execute_command(cfg->argv[i + 1]);
	exit(EXIT_FAILURE);
}
