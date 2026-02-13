/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 16:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/*
** Returns current time in milliseconds.
*/
static long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

/*
** Rendering loop callback function.
** Updates input, renders frame if needed, and calculates FPS.
*/
static int	render_loop(void *param)
{
	t_gui		*gui;
	long long	current_time;
	double		delta;

	gui = (t_gui *)param;
	current_time = get_time_ms();
	if (gui->render.last_time > 0)
	{
		delta = (current_time - gui->render.last_time) / 1000.0;
		if (delta > 0)
			gui->render.fps = 0.9 * gui->render.fps + 0.1 * (1.0 / delta);
	}
	gui->render.last_time = current_time;
	gui_update_input(gui);
	if (gui->render.dirty || gui->render.last_dirty)
	{
		gui_render(gui);
		if (!gui->render.dirty)
			gui->render.last_dirty = false;
		else
			gui->render.last_dirty = true;
		gui->render.dirty = false;
	}
	return (0);
}

/*
** Starts the main GUI loop.
*/
void	gui_loop(t_gui *gui)
{
	mlx_hook(gui->win.win, KeyPress, KeyPressMask, key_press, gui);
	mlx_hook(gui->win.win, KeyRelease, KeyReleaseMask, key_release, gui);
	mlx_hook(gui->win.win, ButtonPress, ButtonPressMask, mouse_click, gui);
	mlx_hook(gui->win.win, ButtonRelease, ButtonReleaseMask, mouse_release,
		gui);
	mlx_hook(gui->win.win, MotionNotify, PointerMotionMask, mouse_motion, gui);
	mlx_hook(gui->win.win, 17, 0, gui_window_close, gui);
	mlx_loop_hook(gui->win.mlx, (int (*)())render_loop, gui);
	mlx_loop(gui->win.mlx);
}
