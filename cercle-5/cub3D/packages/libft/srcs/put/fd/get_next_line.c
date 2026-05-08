/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:13:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/26 01:15:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fds[MAX_FDS];

/**
 * @brief Executes public extract_remainder utility.
 * @note Public library exported function.
 */
char	*extract_remainder(char *buffer, int newline_pos)
{
	char	*remainder;
	size_t	remainder_len;

	remainder_len = ft_strlen(buffer + newline_pos + 1);
	if (remainder_len > 0)
		remainder = ft_substr(buffer, newline_pos + 1, remainder_len);
	else
		remainder = NULL;
	return (remainder);
}

/**
 * @brief Executes public consume_line utility.
 * @note Public library exported function.
 */
char	*consume_line(char **fds, int fd)
{
	int		l;
	char	*str;
	char	*old_buffer;

	if (!fds[fd])
		return (NULL);
	l = gnl_strchr_idx(fds[fd], '\n');
	if (l == -1)
	{
		if (ft_strlen(fds[fd]) == 0)
			return (NULL);
		str = ft_substr(fds[fd], 0, ft_strlen(fds[fd]));
		free(fds[fd]);
		fds[fd] = NULL;
		return (str);
	}
	str = ft_substr(fds[fd], 0, l + 1);
	old_buffer = fds[fd];
	fds[fd] = extract_remainder(old_buffer, l);
	free(old_buffer);
	return (str);
}

/**
 * @brief Executes public read_line utility.
 * @note Public library exported function.
 */
char	*read_line(char **fds, int fd, char *buffer)
{
	int	bytes;

	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		buffer[bytes] = 0;
		fds[fd] = gnl_realloc(fds[fd], buffer);
		if (!fds[fd])
		{
			free(buffer);
			return (NULL);
		}
		if (ft_strchr(fds[fd], '\n'))
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

/**
 * @brief Reads a line from a file descriptor.
 * @note Public library exported function.
 */
void	get_next_line_reset(int fd)
{
	if (fd < 0 || fd >= MAX_FDS)
		return ;
	if (fds[fd])
		fds[fd] = gnl_free(fds, fd);
}

char	*get_next_line(int fd)
{
	char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	return (read_line(fds, fd, buffer));
}
