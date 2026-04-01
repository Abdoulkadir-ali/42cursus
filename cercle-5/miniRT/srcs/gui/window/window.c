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

#include "window.h"

/*
** Handles window resize events.
** Recreates only the display image to match the new window dimensions.
** The render image stays at the fixed render resolution.
*/
int	gui_window_resize(t_vec2i size, t_gui *gui)
{
	void	*new_img;

	if (size.x < 200 || size.y < 150)
		return (0);
	if (size.x == gui->win.disp_size.x && size.y == gui->win.disp_size.y)
		return (0);
	new_img = mlx_new_image(gui->win.mlx, size.x, size.y);
	if (!new_img)
		return (0);
	if (gui->win.disp_img)
		mlx_destroy_image(gui->win.mlx, gui->win.disp_img);
	gui->win.disp_size = size;
	gui->win.disp_img = new_img;
	gui->win.disp_addr = mlx_get_data_addr(gui->win.disp_img,
			&gui->win.disp_bpp, &gui->win.disp_line_len,
			&gui->win.disp_endian);
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
