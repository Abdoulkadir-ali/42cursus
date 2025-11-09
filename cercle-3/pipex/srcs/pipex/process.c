/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:11:33 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 16:07:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	run_process(int i, int nb, t_pipe *pipes, char **argv)
{
	if (i == 0 && i == nb - 1)
	{
		read_from_infile(argv[0], pipes, nb);
		write_to_outfile(argv[nb + 1], pipes, i, nb);
	}
	else if (i == 0)
		read_from_infile(argv[0], pipes, nb);
	else if (i == nb - 1)
		write_to_outfile(argv[nb + 1], pipes, i, nb);
	else
	{
		dup2(pipes[i - 1][READ_END], STDIN_FILENO);
		dup2(pipes[i][WRITE_END], STDOUT_FILENO);
	}
	if (nb > 1)
	{
		close_all_pipes(pipes, nb - 1);
		free(pipes);
	}
	execute_command(argv[i + 1]);
	exit(EXIT_FAILURE);
}
