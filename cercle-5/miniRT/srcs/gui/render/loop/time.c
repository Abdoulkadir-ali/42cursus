/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 13:04:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

double	update_delta(t_gui *gui)
{
	long long	current_time;
	double		delta;

	current_time = get_time_ms();
	if (gui->render.last_time > 0)
	{
		delta = (current_time - gui->render.last_time) / 1000.0;
		if (delta > 0)
			gui->render.fps = 0.9 * gui->render.fps + 0.1 * (1.0 / delta);
	}
	else
		delta = 0.016;
	gui->render.last_time = current_time;
	return (delta);
}
