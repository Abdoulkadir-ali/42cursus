/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 19:59:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

#include "graphics.h"
#include "map.h"
#include <dirent.h>

static int	is_fdf_file(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".fdf", 4) == 0);
}

static int	count_fdf_files(DIR *dir)
{
	struct dirent	*entry;
	int				count;

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

void	init_map_list(t_map_manager *m)
{
	DIR	*dir;
	int	count;

	dir = opendir("maps/test_maps");
	if (!dir)
	{
		m->map_files = NULL;
		m->maps = NULL;
		m->count = 0;
		return ;
	}
	count = count_fdf_files(dir);
	closedir(dir);
	m->map_files = malloc(sizeof(char *) * count);
	m->maps = malloc(sizeof(t_map *) * count);
	m->count = count;
	dir = opendir("maps/test_maps");
	load_map_files(m, dir, count);
	closedir(dir);
	m->current_index = 0;
}

void	load_map_files(t_map_manager *m, DIR *dir, int count)
{
	struct dirent	*entry;
	char			path[256];
	int				i;

	i = 0;
	rewinddir(dir);
	entry = readdir(dir);
	while (entry && i < count)
	{
		if (is_fdf_file(entry->d_name))
		{
			m->map_files[i] = ft_strdup(entry->d_name);
			ft_strlcpy(path, "maps/test_maps/", sizeof(path));
			ft_strlcat(path, entry->d_name, sizeof(path));
			m->maps[i] = load_map(path);
			i++;
		}
		entry = readdir(dir);
	}
}

void	cycle_map(t_map_manager *m, t_map **current_map)
{
	if (!m->maps || m->count == 0)
		return ;
	m->current_index = (m->current_index + 1) % m->count;
	*current_map = m->maps[m->current_index];
}
