/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/07 23:47:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"
#include "optimization.h"
#include "window.h"
#include <sys/time.h>

static long	get_elapsed_us(struct timeval *last, struct timeval *now)
{
	long	elapsed;

	if (gettimeofday(now, NULL) != 0)
		return (16667);
	if (last->tv_sec == 0 && last->tv_usec == 0)
	{
		*last = *now;
		return (16667);
	}
	elapsed = (now->tv_sec - last->tv_sec) * 1000000L + (now->tv_usec
			- last->tv_usec);
	if (elapsed <= 0)
		elapsed = 16667;
	*last = *now;
	return (elapsed);
}

int	on_loop(void *param)
{
	t_app					*app;
	static struct timeval	last = {0, 0};
	static int				first_frame = 1;
	struct timeval			now;
	long					elapsed_us;

	app = (t_app *)param;
	if (first_frame)
		first_frame = 0;
	elapsed_us = get_elapsed_us(&last, &now);
	update_gameplay(app->world, (int)elapsed_us);
	update_optimization(app->world, (int)elapsed_us);
	render_gameplay(app->window, app->world);
	return (0);
}

void	setup_gameplay_hooks(t_app *app)
{
	mlx_hook(app->window->win, 2, 1L << 0, (void *)on_key_press, app);
	mlx_hook(app->window->win, 3, 1L << 1, (void *)on_key_release, app);
	mlx_hook(app->window->win, 17, 0, (void *)on_destroy, app);
	setup_resize_hook(app);
	mlx_loop_hook(app->window->mlx, (void *)on_loop, app);
	init_mouse_hook(app->window, &app->world->player.controller);
}
