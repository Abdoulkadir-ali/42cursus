/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/*
** Handles window resize events.
** Recreates the MLX image buffer to match the new window dimensions.
*/
int	gui_window_resize(int width, int height, t_gui *gui)
{
	if (width < 100 || height < 100)
		return (0);
	if (gui->win.img)
		mlx_destroy_image(gui->win.mlx, gui->win.img);
	gui->win.width = width;
	gui->win.height = height;
	gui->win.img = mlx_new_image(gui->win.mlx, width, height);
	gui->win.addr = mlx_get_data_addr(gui->win.img, &gui->win.bpp,
			&gui->win.line_len, &gui->win.endian);
	gui->render.dirty = true;
	return (0);
}

/*
** Handles window close events (e.g. clicking the X button).
*/
int	gui_window_close(t_gui *gui)
{
	mlx_loop_end(gui->win.mlx);
	return (0);
}
