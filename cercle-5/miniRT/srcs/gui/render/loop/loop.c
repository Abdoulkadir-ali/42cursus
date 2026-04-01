/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 17:18:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	render_if_dirty(t_gui *gui)
{
	if (!gui->render.dirty && !gui->render.last_dirty)
		return ;
	gui_render(gui);
	if (!gui->render.dirty)
		gui->render.last_dirty = false;
	else
		gui->render.last_dirty = true;
	gui->render.dirty = false;
}

static int	render_loop(void *param)
{
	t_gui	*gui;
	double	delta;

	gui = (t_gui *)param;
	poll_map_job(gui);
	delta = update_delta(gui);
	update_animations(gui, delta);
	update_physics_step(gui, delta);
	update_autorefresh(gui);
	update_ambient(gui);
	gui_update_input(gui);
	render_if_dirty(gui);
	return (0);
}

void	gui_loop(t_gui *gui)
{
	mlx_hook(gui->win.win, KeyPress, KeyPressMask, key_press, gui);
	mlx_hook(gui->win.win, KeyRelease, KeyReleaseMask, key_release, gui);
	mlx_hook(gui->win.win, ButtonPress, ButtonPressMask, mouse_click_hook(), gui);
	mlx_hook(gui->win.win, ButtonRelease, ButtonReleaseMask, mouse_release_hook(),
		gui);
	mlx_hook(gui->win.win, MotionNotify, PointerMotionMask, mouse_motion_hook(), gui);
	mlx_hook(gui->win.win, 17, 0, gui_window_close, gui);
	mlx_loop_hook(gui->win.mlx, (int (*)())render_loop, gui);
	mlx_loop(gui->win.mlx);
}
