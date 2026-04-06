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

static bool	create_is(t_gui *gui, t_vec2s sz, void **imgs, char **as)
{
	size_t	i;
	int		bpp;
	int		ll;
	int		ed;

	i = 0;
	while (i < 3)
	{
		imgs[i] = mlx_new_image(gui->win.mlx, sz.x, sz.y);
		if (!imgs[i])
		{
			while (i-- > 0)
				mlx_destroy_image(gui->win.mlx, imgs[i]);
			return (false);
		}
		as[i] = mlx_get_data_addr(imgs[i], &bpp, &ll, &ed);
		i++;
	}
	gui->win.disp_bpp = bpp;
	gui->win.disp_line_len = ll;
	gui->win.disp_endian = ed;
	return (true);
}

int	gui_window_resize(t_vec2s sz, t_gui *gui)
{
	void	*imgs[3];
	char	*addrs[3];
	size_t	i;

	if (sz.x < 200 || sz.y < 150)
		return (0);
	if (sz.x == gui->win.disp_size.x && sz.y == gui->win.disp_size.y)
		return (0);
	if (!create_is(gui, sz, imgs, addrs))
		return (0);
	i = 0;
	while (i < 3)
	{
		mlx_destroy_image(gui->win.mlx, gui->win.disp_imgs[i]);
		gui->win.disp_imgs[i] = imgs[i];
		gui->win.disp_addrs[i] = addrs[i];
		i++;
	}
	gui->win.disp_size = sz;
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
	gui_window_resize(vec2s(a.width, a.height), gui);
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
