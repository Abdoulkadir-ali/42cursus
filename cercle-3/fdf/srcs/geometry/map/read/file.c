/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:16:38 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 03:15:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

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

void	load_map_files(t_maps *m, DIR *dir, size_t count, char *dir_path)
{
	struct dirent	*entry;
	char			path[256];
	size_t			i;

	i = 0;
	rewinddir(dir);
	entry = readdir(dir);
	while (entry && i < count)
	{
		if (is_fdf_file(entry->d_name))
		{
			m->map_files[i] = ft_strdup(entry->d_name);
			ft_strlcpy(path, dir_path, sizeof(path));
			if (path[ft_strlen(path) - 1] != '/')
				ft_strlcat(path, "/", sizeof(path));
			ft_strlcat(path, entry->d_name, sizeof(path));
			m->maps[i] = load_map(path);
			i++;
		}
		entry = readdir(dir);
	}
}
