/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:47:02 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 12:49:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	*thread_draw_routine(void *data)
{
	t_thread_data	*d;

	d = (t_thread_data *)data;
	draw_grid_section(d->g, d->start_y, d->end_y, d->step);
	return (NULL);
}

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
