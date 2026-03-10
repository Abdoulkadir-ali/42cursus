/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 04:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/**
 * @brief Allocate thread bookkeeping arrays for map loading.
 * @param res Thread resource container to initialize.
 * @param count Number of worker slots to allocate.
 * @return `1` on success, otherwise `0`.
 */
static int	allocate_thread_resources(t_thread_res *res, size_t count)
{
	res->threads = malloc(sizeof(pthread_t) * count);
	res->active = ft_calloc(count, sizeof(int));
	res->count = count;
	if (!res->threads || !res->active)
	{
		free(res->threads);
		free(res->active);
		return (0);
	}
	return (1);
}

/**
 * @brief Build an absolute path for a discovered map file.
 * @param buf Destination buffer.
 * @param bufsize Size of the destination buffer.
 * @param dir_path Base directory path.
 * @param filename Map filename to append.
 */
static void	build_map_path(char *buf, size_t bufsize, const char *dir_path,
		const char *filename)
{
	ft_strlcpy(buf, dir_path, bufsize);
	if (buf[ft_strlen(buf) - 1] != '/')
		ft_strlcat(buf, "/", bufsize);
	ft_strlcat(buf, filename, bufsize);
}

/**
 * @brief Start one asynchronous map load.
 * @param m Map collection receiving the result.
 * @param res Thread bookkeeping arrays.
 * @param i Destination map index.
 * @param path Absolute path to the map file.
 */
static void	start_load_thread(t_maps *m, t_thread_res *res, size_t i,
		const char *path)
{
	t_load_thread_data	*data;

	data = malloc(sizeof(t_load_thread_data));
	if (data)
	{
		data->m = m;
		data->path = ft_strdup(path);
		data->index = i;
		if (pthread_create(&res->threads[i], NULL, load_map_thread_routine,
				data) == 0)
			res->active[i] = 1;
		else
		{
			m->maps[i] = load_map(path);
			free(data->path);
			free(data);
		}
	}
	else
		m->maps[i] = load_map(path);
}

/**
 * @brief Join all started loader threads and free their resources.
 * @param res Thread resource container to release.
 */
static void	join_and_free_threads(t_thread_res *res)
{
	size_t	j;

	j = 0;
	while (j < res->count)
	{
		if (res->active[j])
			pthread_join(res->threads[j], NULL);
		j++;
	}
	free(res->threads);
	free(res->active);
	res->threads = NULL;
	res->active = NULL;
	res->count = 0;
}

/**
 * @brief Load all discovered map files into the map collection.
 * @param m Map collection receiving the loaded maps.
 * @param dir Open directory stream to enumerate.
 * @param count Number of maps expected in the directory.
 * @param dir_path Base directory for discovered entries.
 */
void	load_map_files(t_maps *m, DIR *dir, size_t count, char *dir_path)
{
	t_load_ctx	ctx;

	if (!allocate_thread_resources(&ctx.res, count))
		return ;
	ctx.i = 0;
	rewinddir(dir);
	ctx.entry = readdir(dir);
	while (ctx.entry && ctx.i < count)
	{
		if (is_fdf_file(ctx.entry->d_name))
		{
			m->map_files[ctx.i] = ft_strdup(ctx.entry->d_name);
			build_map_path(ctx.path, sizeof(ctx.path), dir_path,
				ctx.entry->d_name);
			start_load_thread(m, &ctx.res, ctx.i, ctx.path);
			ctx.i++;
		}
		ctx.entry = readdir(dir);
	}
	join_and_free_threads(&ctx.res);
}
