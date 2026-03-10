/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:16:38 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/**
 * @brief Load one map on a worker thread.
 * @param arg Thread payload describing the map slot and path.
 * @return Always `NULL` after the load completes.
 */
void	*load_map_thread_routine(void *arg)
{
	t_load_thread_data	*data;

	data = (t_load_thread_data *)arg;
	data->m->maps[data->index] = load_map(data->path);
	free(data->path);
	free(data);
	return (NULL);
}

/**
 * @brief Check whether a path points to a directory.
 * @param path Filesystem path to inspect.
 * @return `1` when the path is a directory, otherwise `0`.
 */
int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

/**
 * @brief Check whether a filename ends with the `.fdf` extension.
 * @param filename Filename to inspect.
 * @return `1` for `.fdf` files, otherwise `0`.
 */
int	is_fdf_file(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".fdf", 4) == 0);
}

/**
 * @brief Count `.fdf` entries in an opened directory stream.
 * @param dir Directory stream positioned anywhere.
 * @return Number of discovered map files.
 */
size_t	count_fdf_files(DIR *dir)
{
	struct dirent	*entry;
	size_t			count;

	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (is_fdf_file(entry->d_name))
			count++;
		entry = readdir(dir);
	}
	return (count);
}
