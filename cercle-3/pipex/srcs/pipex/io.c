/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:08:40 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 15:51:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	read_from_infile(char *infile, t_pipe *pipes, int nb)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror(infile);
		close(STDIN_FILENO);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (nb > 1)
		dup2(pipes[0][WRITE_END], STDOUT_FILENO);
	return (0);
}

int	write_to_outfile(char *outfile, t_pipe *pipes, int i, int nb)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(outfile);
		close(STDOUT_FILENO);
	}
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (nb > 1)
		dup2(pipes[i - 1][READ_END], STDIN_FILENO);
	return (0);
}
