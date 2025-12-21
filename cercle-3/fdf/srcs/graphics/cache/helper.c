/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:58:16 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 11:42:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <pthread.h>

void	init_cache(t_graphics *g)
{
	int		needs_update;
	size_t	size;

	needs_update = g->cache.map != g->map || g->cache.width != g->map->width
		|| g->cache.height != g->map->height;
	if (needs_update)
	{
		cleanup_cache(g);
		size = sizeof(t_point) * g->map->width * g->map->height;
		g->cache.points = malloc(size);
		if (!g->cache.points)
			return ;
		g->cache.width = g->map->width;
		g->cache.height = g->map->height;
		g->cache.map = g->map;
	}
}

typedef struct s_fill_cache_thread_data
{
	t_graphics	*g;
	size_t		start_y;
	size_t		end_y;
}				t_fill_cache_thread_data;

static void	*fill_cache_thread(void *arg)
{
	t_fill_cache_thread_data	*data;
	t_fill_cache_ctx			ctx;
	size_t						row_base;

	data = (t_fill_cache_thread_data *)arg;
	ctx.y = data->start_y;
	while (ctx.y < data->end_y)
	{
		row_base = ctx.y * data->g->map->width;
		ctx.x = 0;
		while (ctx.x < data->g->map->width)
		{
			ctx.idx = row_base + ctx.x;
			if (data->g->map->points.pos[ctx.idx].z <= BAD_VALUE + 1.0)
				data->g->cache.points[ctx.idx].pos = create_vec3d(BAD_VALUE,
						BAD_VALUE, BAD_VALUE);
			else
			{
				t_point input_point = {data->g->map->points.pos[ctx.idx], data->g->map->points.color[ctx.idx]};
				ctx.projected = apply_transform(input_point, data->g->camera);
				data->g->cache.points[ctx.idx] = ctx.projected;
			}
			ctx.x++;
		}
		ctx.y++;
	}
	return (NULL);
}

void	fill_cache(t_graphics *g)
{
	pthread_t					threads[NUM_THREADS];
	t_fill_cache_thread_data	thread_data[NUM_THREADS];
	size_t						rows_per_thread;
	size_t						i;

	rows_per_thread = g->map->height / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		thread_data[i].g = g;
		thread_data[i].start_y = i * rows_per_thread;
		if (i == NUM_THREADS - 1)
			thread_data[i].end_y = g->map->height;
		else
			thread_data[i].end_y = (i + 1) * rows_per_thread;
		pthread_create(&threads[i], NULL, fill_cache_thread, &thread_data[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
		pthread_join(threads[i++], NULL);
}
