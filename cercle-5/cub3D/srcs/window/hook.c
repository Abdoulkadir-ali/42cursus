/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 01:19:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "window.h"
#include <X11/Xlib.h>

static void	query_size(t_window *win, int *w, int *h)
{
	XWindowAttributes	attrs;
	Display				*dpy;
	Window				xwin;

	dpy = *(Display **)win->mlx;
	xwin = *(Window *)win->win;
	XGetWindowAttributes(dpy, xwin, &attrs);
	*w = attrs.width;
	*h = attrs.height;
}

static int	on_resize(void *param)
{
	t_app	*app;
	int		w;
	int		h;

	app = (t_app *)param;
	query_size(app->window, &w, &h);
	handle_window_resize(app->window, w, h);
	return (0);
}

void	setup_resize_hook(t_app *app)
{
	mlx_hook(app->window->win, 22, 1L << 17, (void *)on_resize, app);
}
