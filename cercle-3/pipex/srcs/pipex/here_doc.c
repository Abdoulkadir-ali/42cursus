/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 17:02:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*create_temp_filename(void)
{
	char		*pid_str;
	char		*temp_name;
	pid_t		pid;

	pid = getpid();
	pid_str = ft_itoa(pid);
	if (!pid_str)
		return (NULL);
	temp_name = ft_strjoin("/tmp/.heredoc_tmp_", pid_str);
	free(pid_str);
	return (temp_name);
}

static void	read_heredoc_lines(int fd, char *limiter)
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
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

char	*create_here_doc(char *limiter)
{
	char	*temp_file;
	int		fd;

	temp_file = create_temp_filename();
	if (!temp_file)
		return (NULL);
	fd = open(temp_file, O_WRONLY | O_CREAT | O_EXCL, 0600);
	if (fd == -1)
	{
		perror("heredoc temp file");
		return (NULL);
	}
	read_heredoc_lines(fd, limiter);
	close(fd);
	return (temp_file);
}
