/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:58:16 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:31:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Allocate or resize the projection cache for the active map.
 * @param g Graphics state owning the cache and active map.
 */
void	init_cache(t_graphics *g)
{
	size_t	size;

	if (g->cache.map != g->map || g->cache.width != g->map->width
		|| g->cache.height != g->map->height)
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

/**
 * @brief Transform one band of rows into cached projected points.
 * @param arg Thread payload describing the target row range.
 * @return Always `NULL` for pthread compatibility.
 */
static void	*fill_cache_thread(void *arg)
{
	t_fill_cache_thread_data	*data;
	size_t						row_base;
	size_t						y;

	data = (t_fill_cache_thread_data *)arg;
	y = data->start_y;
	while (y < data->end_y)
	{
		row_base = y * data->g->map->width;
		transform_scanline(data->g, data->g->cache.points, row_base,
			data->g->map->width);
		y++;
	}
	return (NULL);
}

/**
 * @brief Fill the projection cache in parallel across map rows.
 * @param g Graphics state owning the active cache and map.
 */
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
