/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:47:02 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:31:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Draw one standard grid section inside a worker thread.
 * @param data Thread payload describing the row range and LOD step.
 * @return Always `NULL` for pthread compatibility.
 */
void	*thread_draw_routine(void *data)
{
	t_thread_data	*d;

	d = (t_thread_data *)data;
	draw_grid_section(d->g, d->start_y, d->end_y, d->lod_value);
	return (NULL);
}

/**
 * @brief Join all worker threads used by the grid drawing pass.
 * @param threads Thread array to join.
 */
void	join_threads(pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
