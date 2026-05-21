/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:22:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 05:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*read_loop(int fd, char *buf, size_t cap)
{
	ssize_t	n;
	size_t	len;
	char	*tmp;

	len = 0;
	while (1)
	{
		if (len + 1024 >= cap)
		{
			cap *= 2;
			tmp = (char *)realloc(buf, cap);
			if (!tmp)
				return (free(buf), NULL);
			buf = tmp;
		}
		n = read(fd, buf + len, cap - len - 1);
		if (n <= 0)
			break ;
		len += (size_t)n;
	}
	buf[len] = '\0';
	return (buf);
}

/* Read whole file into a malloc'd null-terminated buffer. */
char	*read_file_all(const char *path)
{
	int		fd;
	char	*buf;
	size_t	cap;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	cap = 4096;
	buf = (char *)malloc(cap);
	if (!buf)
	{
		close(fd);
		return (NULL);
	}
	buf = read_loop(fd, buf, cap);
	close(fd);
	return (buf);
}
