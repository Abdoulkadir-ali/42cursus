/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 16:17:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../gnl/get_next_line.h"

void	read_here_doc(char *limiter, int write_fd)
{
	char	*line;
	size_t	limiter_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, limiter_len) == 0
			&& (line[limiter_len] == '\n' || line[limiter_len] == '\0'))
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		free(line);
	}
	close(write_fd);
}

int	handle_here_doc(char *limiter)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		close(pipefd[READ_END]);
		read_here_doc(limiter, pipefd[WRITE_END]);
		exit(0);
	}
	close(pipefd[WRITE_END]);
	waitpid(pid, NULL, 0);
	dup2(pipefd[READ_END], STDIN_FILENO);
	close(pipefd[READ_END]);
	return (0);
}

int	write_to_outfile_append(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(outfile);
		close(STDOUT_FILENO);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
