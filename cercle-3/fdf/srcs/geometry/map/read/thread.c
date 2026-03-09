/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 04:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 04:46:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

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

static void	build_map_path(char *buf, size_t bufsize, const char *dir_path,
		const char *filename)
{
	ft_strlcpy(buf, dir_path, bufsize);
	if (buf[ft_strlen(buf) - 1] != '/')
		ft_strlcat(buf, "/", bufsize);
	ft_strlcat(buf, filename, bufsize);
}

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
