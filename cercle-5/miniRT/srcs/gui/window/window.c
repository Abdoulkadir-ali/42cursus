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

#include "editor.h"

/*
** Handles window resize events.
** Recreates only the display image to match the new window dimensions.
** The render image stays at the fixed render resolution.
*/
int	gui_window_resize(int width, int height, t_gui *gui)
{
	void	*new_img;

	if (width < 200 || height < 150)
		return (0);
	if (width == gui->win.disp_w && height == gui->win.disp_h)
		return (0);
	new_img = mlx_new_image(gui->win.mlx, width, height);
	if (!new_img)
		return (0);
	if (gui->win.disp_img)
		mlx_destroy_image(gui->win.mlx, gui->win.disp_img);
	gui->win.disp_w = width;
	gui->win.disp_h = height;
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
