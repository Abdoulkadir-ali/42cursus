/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:16:38 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 04:38:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

void	*load_map_thread_routine(void *arg)
{
	t_load_thread_data	*data;

	data = (t_load_thread_data *)arg;
	data->m->maps[data->index] = load_map(data->path);
	free(data->path);
	free(data);
	return (NULL);
}

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

static int	is_fdf_file(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".fdf", 4) == 0);
}

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
