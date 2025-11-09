/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:44:22 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 15:43:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipe	*create_pipes(int nb)
{
	t_pipe	*pipes;
	int		i;

	pipes = malloc(sizeof(t_pipe) * (nb - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < nb - 1)
	{
		if (pipe(pipes[i++]) == -1)
		{
			exit_statement("Failed to create pipes\n", pipes, 0);
			return (NULL);
		}
	}
	return (pipes);
}

int	close_all_pipes(t_pipe *pipes, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		close(pipes[i][WRITE_END]);
		close(pipes[i][READ_END]);
		i++;
	}
	return (0);
}
