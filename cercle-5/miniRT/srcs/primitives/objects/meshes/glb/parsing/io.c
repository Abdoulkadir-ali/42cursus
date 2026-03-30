/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:34:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * Reads a GLB file from disk into a single memory buffer.
 */
void	*glb_read_file(const char *path, size_t *size)
{
	int		fd;
	void	*buf;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	*size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	buf = malloc(*size);
	if (!buf)
	{
		close(fd);
		return (NULL);
	}
	read(fd, buf, *size);
	close(fd);
	return (buf);
}
