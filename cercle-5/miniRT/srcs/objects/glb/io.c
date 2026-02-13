/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static bool	read_header(int fd, t_glb_header *h)
{
	if (read(fd, h, 12) < 12)
		return (false);
	if (h->magic != GLB_MAGIC)
		return (false);
	return (true);
}

static bool	read_json_chunk(int fd, char **json)
{
	t_chunk_header	c;

	if (read(fd, &c, 8) < 8)
		return (false);
	if (c.type != CHUNK_JSON)
		return (false);
	*json = ft_calloc(1, c.length + 1);
	if (!*json)
		return (false);
	if (read(fd, *json, c.length) < (ssize_t)c.length)
	{
		free(*json);
		*json = NULL;
		return (false);
	}
	return (true);
}

static bool	read_bin_chunk(int fd, char **bin)
{
	t_chunk_header	c;

	if (read(fd, &c, 8) < 8)
		return (false);
	if (c.type != CHUNK_BIN)
		return (false);
	*bin = malloc(c.length);
	if (!*bin)
		return (false);
	if (read(fd, *bin, c.length) < (ssize_t)c.length)
	{
		free(*bin);
		*bin = NULL;
		return (false);
	}
	return (true);
}

bool	glb_read_buffers(int fd, char *buf[2])
{
	t_glb_header	h;

	if (!read_header(fd, &h))
		return (false);
	if (!read_json_chunk(fd, &buf[0]))
		return (false);
	if (!read_bin_chunk(fd, &buf[1]))
	{
		free(buf[0]);
		buf[0] = NULL;
		return (false);
	}
	return (true);
}
