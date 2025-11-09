/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:13:10 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 16:47:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	find_newline(char *str)
{
	char	*pos;

	if (!str)
		return (-1);
	pos = ft_strchr(str, '\n');
	if (!pos)
		return (-1);
	return (pos - str);
}

char	*extract_remainder(char *buffer, int newline_pos)
{
	char	*remainder;
	int		remainder_len;

	remainder_len = ft_strlen(buffer + newline_pos + 1);
	if (remainder_len > 0)
		remainder = ft_strldup(buffer + newline_pos + 1, remainder_len);
	else
		remainder = NULL;
	return (remainder);
}

char	*consume_line(char **fds, int fd)
{
	int		l;
	char	*str;
	char	*old_buffer;

	if (!fds[fd])
		return (NULL);
	l = find_newline(fds[fd]);
	if (l == -1)
	{
		if (ft_strlen(fds[fd]) == 0)
			return (NULL);
		str = ft_strldup(fds[fd], ft_strlen(fds[fd]));
		free(fds[fd]);
		fds[fd] = NULL;
		return (str);
	}
	str = ft_strldup(fds[fd], l + 1);
	old_buffer = fds[fd];
	fds[fd] = extract_remainder(old_buffer, l);
	free(old_buffer);
	return (str);
}

char	*read_line(char **fds, int fd, char *buffer)
{
	int	bytes;

	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		buffer[bytes] = 0;
		fds[fd] = ft_realloc(fds[fd], buffer);
		if (!fds[fd])
		{
			free(buffer);
			return (NULL);
		}
		if (find_newline(fds[fd]) >= 0)
		{
			free(buffer);
			return (consume_line(fds, fd));
		}
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes < 0)
		return (gnl_free(fds, fd));
	return (consume_line(fds, fd));
}

char	*get_next_line(int fd)
{
	static char	*fds[MAX_FDS];
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	return (read_line(fds, fd, buffer));
}
