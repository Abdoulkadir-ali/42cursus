/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_threaded.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:00:00 by abdoali          #+#    #+#             */
/*   Updated: 2025/12/23 20:00:00 by abdoali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_grid_raycast_threaded(t_graphics *g)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	args[NUM_THREADS];
	int				i;
	size_t			strip_width;

	strip_width = g->window->width / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		args[i].g = g;
		args[i].min_visible_x = i * strip_width;
		if (i == NUM_THREADS - 1)
			args[i].max_visible_x = g->window->width;
		else
			args[i].max_visible_x = (i + 1) * strip_width;
		pthread_create(&threads[i], NULL, thread_raycast_routine, &args[i]);
		i++;
	}
	join_threads(threads);
}

void	draw_grid_threaded(t_graphics *g)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	args[NUM_THREADS];
	float			lod_value;
	int				i;
	int				h_step;

	lod_value = g->render_config.lod_value;
	h_step = g->map->height / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		args[i].g = g;
		args[i].lod_value = lod_value;
		args[i].start_y = i * h_step;
		if (i == NUM_THREADS - 1)
			args[i].end_y = g->map->height;
		else
			args[i].end_y = (i + 1) * h_step;
		pthread_create(&threads[i], NULL, thread_draw_routine, &args[i]);
		i++;
	}
	join_threads(threads);
}
