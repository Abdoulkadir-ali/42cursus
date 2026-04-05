/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 18:51:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	gui_loop(t_gui *gui)
{
	ft_print_debug("DEBUG: Setting up MLX hooks\n");
	mlx_hook(gui->win.win, KeyPress, (1L << 0), key_press, gui);
	mlx_hook(gui->win.win, KeyRelease, (1L << 1), key_release, gui);
	mlx_hook(gui->win.win, ButtonPress, (1L << 2), mouse_click_hook(), gui);
	mlx_hook(gui->win.win, ButtonRelease, (1L << 3), mouse_release_hook(), gui);
	mlx_hook(gui->win.win, MotionNotify, (1L << 6), mouse_motion_hook(), gui);
	mlx_hook(gui->win.win, DestroyNotify, 0, gui_window_close, gui);
	mlx_hook(gui->win.win, 22, (1L << 17), gui_resize_hook, gui);
	mlx_loop_hook(gui->win.mlx, (int (*)(void *))gui_update, gui);
	ft_print_debug("DEBUG: Spawning render thread\n");
	pthread_create(&gui->render.render_thread, NULL, render_thread_func, gui);
	ft_print_debug("DEBUG: Entering MLX loop\n");
	mlx_loop(gui->win.mlx);
	pthread_mutex_lock(&gui->render.job_mutex);
	gui->render.job_stop = 1;
	pthread_mutex_unlock(&gui->render.job_mutex);
	pthread_join(gui->render.render_thread, NULL);
}
