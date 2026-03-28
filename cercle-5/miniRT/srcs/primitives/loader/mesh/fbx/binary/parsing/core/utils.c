/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:38:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Reads entire file content into a malloc'd buffer.
 */
char	*fbx_read_file(const char *path, size_t *out_size)
{
	int			fd;
	struct stat	st;
	char		*buf;

	fd = open(path, O_RDONLY);
	if (fd < 0 || fstat(fd, &st) < 0)
		return (NULL);
	buf = malloc(st.st_size + 1);
	if (buf != NULL)
	{
		if (read(fd, buf, st.st_size) != (ssize_t)st.st_size)
			buf[0] = '\0';
		buf[st.st_size] = '\0';
		*out_size = st.st_size;
	}
	close(fd);
	return (buf);
}

/**
 * @brief Simple string finder for FBX ASCII nodes.
 */
char	*fbx_find_node(char *start, char *end, const char *key)
{
	char	*p;
	size_t	len;

	len = ft_strlen(key);
	p = start;
	while (p < end - len)
	{
		if (ft_strncmp(p, key, len) == 0)
			return (p);
		p++;
	}
	return (NULL);
}
