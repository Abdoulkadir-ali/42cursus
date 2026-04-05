/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 17:58:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <sys/time.h>



static double	frame_delta(long long *last_ms)
{
	long long	now;
	double		dt;

	now = now_ms();
	dt = (*last_ms > 0) ? (now - *last_ms) / 1000.0 : 0.016;
	*last_ms = now;
	if (dt > 0.1)
		dt = 0.1;
	return (dt);
}

static void	render_frame(t_gui *gui, double delta)
{
	if (!gui || delta == 0.0)
	{
		ft_print_debug("[RENDER] render_frame: invalid state (gui=%p delta=%f)\n", (void *)gui, delta);
		return ;
	}
	cmd_drain(gui);
	scene_swap_step(gui);
	physics_step(gui, delta);
	anim_step(gui, delta);
	bvh_step(gui);
	raytrace_step(gui, delta);
}

/*
** Render thread entry point.  Free-running sequential loop — owns all
** simulation and tracing.  Shutdown is signalled via job_stop flag.
*/
void	*render_thread_func(void *arg)
{
	t_gui		*gui;
	long long	last_ms;
	double		delta;

	gui = (t_gui *)arg;
	last_ms = 0;
	while (1)
	{
		pthread_mutex_lock(&gui->render.job_mutex);
		if (gui->render.job_stop)
		{
			pthread_mutex_unlock(&gui->render.job_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&gui->render.job_mutex);
		delta = frame_delta(&last_ms);
		render_frame(gui, delta);
	}
	return (NULL);
}
