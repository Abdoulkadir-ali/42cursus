/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 13:16:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <pthread.h>

void	draw_grid(t_graphics *g)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	args[NUM_THREADS];
	int				step;
	int				i;
	int				h_step;

	step = g->render_config.lod_level;
	h_step = g->map->height / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		args[i].g = g;
		args[i].step = step;
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

void	draw_grid_section(t_graphics *g, int start_y, int end_y, int step)
{
	int	y;

	y = start_y;
	while (y < end_y)
	{
		draw_grid_row(g, y, step);
		y += step;
	}
}
