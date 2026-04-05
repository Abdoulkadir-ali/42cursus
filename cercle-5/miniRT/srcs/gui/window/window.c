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
** Handles window resize events synchronously.
** Destroys old display images and creates new ones at the new size,
** then recomputes layout and marks the frame dirty.
*/
int	gui_window_resize(t_vec2i size, t_gui *gui)
{
	void	*imgs[3];
	char	*addrs[3];
	int		line_len;
	int		bpp;
	int		endian;
	int		i;

	if (size.x < 200 || size.y < 150)
		return (0);
	if (size.x == gui->win.disp_size.x && size.y == gui->win.disp_size.y)
		return (0);
	i = 0;
	while (i < 3)
	{
		imgs[i] = mlx_new_image(gui->win.mlx, size.x, size.y);
		if (!imgs[i])
		{
			while (--i >= 0)
				mlx_destroy_image(gui->win.mlx, imgs[i]);
			return (0);
		}
		i++;
	}
	addrs[0] = mlx_get_data_addr(imgs[0], &bpp, &line_len, &endian);
	addrs[1] = mlx_get_data_addr(imgs[1], &bpp, &line_len, &endian);
	addrs[2] = mlx_get_data_addr(imgs[2], &bpp, &line_len, &endian);
	i = 0;
	while (i < 3)
	{
		mlx_destroy_image(gui->win.mlx, gui->win.disp_imgs[i]);
		gui->win.disp_imgs[i] = imgs[i];
		gui->win.disp_addrs[i] = addrs[i];
		i++;
	}
	gui->win.disp_line_len = line_len;
	gui->win.disp_bpp = bpp;
	gui->win.disp_endian = endian;
	gui->win.disp_size = size;
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
