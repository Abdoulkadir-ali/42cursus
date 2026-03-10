/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:40:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:23:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Return the current wall-clock time in milliseconds.
 * @return Current time in milliseconds.
 */
static long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Update the rolling FPS counters stored in the graphics frame data.
 * @param events Event context owning the graphics frame-data state.
 */
void	calculate_fps(t_events *events)
{
	long			current_time;
	t_frame_data	*f;

	f = &events->graphics->frame_data;
	current_time = get_time_ms();
	if (f->last_check == 0)
		f->last_check = current_time;
	f->frame_count++;
	if (current_time - f->last_check >= 250)
	{
		f->fps = (f->frame_count * 1000) / (current_time - f->last_check);
		f->frame_count = 0;
		f->last_check = current_time;
	}
}
