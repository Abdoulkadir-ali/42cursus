/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:16:38 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/28 20:04:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#include <pthread.h>

typedef struct s_load_thread_data
{
	t_maps	*m;
	char	*path;
	size_t	index;
}			t_load_thread_data;

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

void	load_map_files(t_maps *m, DIR *dir, size_t count, char *dir_path)
{
	struct dirent		*entry;
	char				path[256];
	size_t				i;
	pthread_t			*threads;
	int					*active;
	t_load_thread_data	*data;
	size_t				j;

	threads = malloc(sizeof(pthread_t) * count);
	active = ft_calloc(count, sizeof(int));
	if (!threads || !active)
	{
		free(threads);
		free(active);
		return ;
	}
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
			data = malloc(sizeof(t_load_thread_data));
			if (data)
			{
				data->m = m;
				data->path = ft_strdup(path);
				data->index = i;
				if (pthread_create(&threads[i], NULL, load_map_thread_routine,
						data) == 0)
					active[i] = 1;
				else
				{
					m->maps[i] = load_map(path);
					free(data->path);
					free(data);
				}
			}
			else
				m->maps[i] = load_map(path);
			i++;
		}
		entry = readdir(dir);
	}
	j = 0;
	while (j < i)
	{
		if (active[j])
			pthread_join(threads[j], NULL);
		j++;
	}
	free(threads);
	free(active);
}
