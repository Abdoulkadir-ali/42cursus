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
#include "editor.h"

/*
** Handles window resize events.
** Recreates only the display image to match the new window dimensions.
** The render image stays at the fixed render resolution.
*/
int	gui_window_resize(t_vec2i size, t_gui *gui)
{
	void	*new_img0;
	void	*new_img1;

	if (size.x < 200 || size.y < 150)
		return (0);
	if (size.x == gui->win.disp_size.x && size.y == gui->win.disp_size.y)
		return (0);
	new_img0 = mlx_new_image(gui->win.mlx, size.x, size.y);
	if (!new_img0)
		return (0);
	new_img1 = mlx_new_image(gui->win.mlx, size.x, size.y);
	if (!new_img1)
	{
		mlx_destroy_image(gui->win.mlx, new_img0);
		return (0);
	}
	pthread_mutex_lock(&gui->win.disp_mutex);
	if (gui->win.disp_imgs[0])
		mlx_destroy_image(gui->win.mlx, gui->win.disp_imgs[0]);
	if (gui->win.disp_imgs[1])
		mlx_destroy_image(gui->win.mlx, gui->win.disp_imgs[1]);
	gui->win.disp_size = size;
	gui->win.disp_imgs[0] = new_img0;
	gui->win.disp_addrs[0] = mlx_get_data_addr(gui->win.disp_imgs[0],
			&gui->win.disp_bpp, &gui->win.disp_line_len,
			&gui->win.disp_endian);
	gui->win.disp_imgs[1] = new_img1;
	gui->win.disp_addrs[1] = mlx_get_data_addr(gui->win.disp_imgs[1],
			&gui->win.disp_bpp, &gui->win.disp_line_len,
			&gui->win.disp_endian);
	pthread_mutex_unlock(&gui->win.disp_mutex);
	gui_recompute_layout(gui);
	gui->render.dirty = true;
	return (0);
}

int	gui_resize_hook(t_gui *gui)
{
	Display				*dpy;
	Window				xwin;
	XWindowAttributes	a;

	dpy = *(Display **)gui->win.mlx;
	xwin = *(Window *)gui->win.win;
	if (!XGetWindowAttributes(dpy, xwin, &a))
		return (0);
	gui_window_resize(vec2i(a.width, a.height), gui);
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
