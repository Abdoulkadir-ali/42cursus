/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 05:12:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "window.h"

static void	make_resizable(t_app *app)
{
	t_xvar		*xv;
	t_win_list	*wl;
	XSizeHints	hints;

	xv = (t_xvar *)app->mlx;
	wl = (t_win_list *)app->win;
	memset(&hints, 0, sizeof(hints));
	hints.flags = PMinSize | PResizeInc;
	hints.min_width = MIN_WIN_W;
	hints.min_height = MIN_WIN_H;
	hints.width_inc = 1;
	hints.height_inc = 1;
	XSetWMNormalHints(xv->display, wl->window, &hints);
}

int	window_init(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		return (-1);
	app->win_w = WIN_W;
	app->win_h = WIN_H;
	app->win = mlx_new_window(app->mlx, app->win_w, app->win_h, "miniRT");
	if (!app->win)
		return (-1);
	make_resizable(app);
	app->img.w = app->win_w;
	app->img.h = app->win_h;
	app->render_w = app->win_w;
	app->render_h = app->win_h;
	app->img.img = mlx_new_image(app->mlx, app->img.w, app->img.h);
	if (!app->img.img)
		return (-1);
	app->img.addr = mlx_get_data_addr(app->img.img, &app->img.bpp,
			&app->img.line_len, &app->img.endian);
	if (pick_alloc(&app->pick, app->img.w, app->img.h) < 0)
		return (-1);
	return (0);
}

int	window_resize(t_app *app, int new_w, int new_h)
{
	if (new_w < MIN_WIN_W)
		new_w = MIN_WIN_W;
	if (new_h < MIN_WIN_H)
		new_h = MIN_WIN_H;
	if (new_w == app->img.w && new_h == app->img.h)
		return (0);
	mlx_destroy_image(app->mlx, app->img.img);
	app->img.w = new_w;
	app->img.h = new_h;
	app->win_w = new_w;
	app->win_h = new_h;
	app->render_w = new_w;
	app->render_h = new_h;
	app->img.img = mlx_new_image(app->mlx, app->img.w, app->img.h);
	if (!app->img.img)
		return (-1);
	app->img.addr = mlx_get_data_addr(app->img.img, &app->img.bpp,
			&app->img.line_len, &app->img.endian);
	if (pick_alloc(&app->pick, app->img.w, app->img.h) < 0)
		return (-1);
	pool_rebuild_tiles(&app->pool, app->img.w, app->img.h);
	camera_setup(&app->scene.cam, app->img.w, app->img.h);
	app->dirty = 1;
	return (0);
}

void	poll_window_size(t_app *app)
{
	t_xvar				*xv;
	t_win_list			*wl;
	XWindowAttributes	wa;

	xv = (t_xvar *)app->mlx;
	wl = (t_win_list *)app->win;
	if (!XGetWindowAttributes(xv->display, wl->window, &wa))
		return ;
	if (wa.width != app->img.w || wa.height != app->img.h)
		window_resize(app, wa.width, wa.height);
}

void	window_loop(t_app *app)
{
	mlx_hook(app->win, 17, 0L, on_close, app);
	mlx_hook(app->win, 2, 1L << 0, on_keydown, app);
	mlx_hook(app->win, 3, 1L << 1, on_keyup, app);
	mlx_hook(app->win, 4, 1L << 2, on_mousedown, app);
	mlx_hook(app->win, 5, 1L << 3, on_mouseup, app);
	mlx_hook(app->win, 6, 1L << 6, on_mousemove, app);
	mlx_loop_hook(app->mlx, on_loop, app);
	mlx_loop(app->mlx);
}