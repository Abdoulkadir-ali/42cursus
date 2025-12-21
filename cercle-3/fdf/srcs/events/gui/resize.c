/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:32:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 00:33:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <X11/Xlib.h>

static void	free_buffers(t_window *win)
{
	if (win->z_buffer)
	{
		free(win->z_buffer);
		win->z_buffer = NULL;
	}
	if (win->main_img.img)
	{
		mlx_destroy_image(win->mlx_ptr, win->main_img.img);
		win->main_img.img = NULL;
	}
	if (win->gui_img.img)
	{
		mlx_destroy_image(win->mlx_ptr, win->gui_img.img);
		win->gui_img.img = NULL;
	}
}

static int	recreate_buffers(t_window *win)
{
	if (!init_window_main_image(win, win->mlx_ptr))
		return (0);
	win->gui_img.img = mlx_new_image(win->mlx_ptr, GUI_PANEL_WIDTH, win->height);
	if (!win->gui_img.img)
		return (0);
	int	bpp;
	int	line_len;

	win->gui_img.img_addr = mlx_get_data_addr(win->gui_img.img,
			&bpp, &line_len,
			&win->gui_img.img_endian);
	win->gui_img.img_bpp = (size_t)bpp;
	win->gui_img.img_line_len = (size_t)line_len;
	return (win->gui_img.img_addr != NULL);
}

int	handle_resize(t_events *events)
{
	t_window		*win;
	XWindowAttributes	attrs;
	t_mlx_ptr		*mlx;
	t_mlx_win_list		*win_list;

	win = events->window;
	mlx = (t_mlx_ptr *)win->mlx_ptr;
	win_list = (t_mlx_win_list *)win->ptr;
	XGetWindowAttributes((Display *)mlx->display, (Window)win_list->window, &attrs);
	if ((size_t)attrs.width != win->width || (size_t)attrs.height != win->height)
	{
		recenter_camera_on_resize(events->camera, win->width, win->height,
			attrs.width, attrs.height);
		win->width = attrs.width;
		win->height = attrs.height;
		free_buffers(win);
		if (!recreate_buffers(win))
			cleanup_and_exit(events);
		redraw(events);
	}
	return (0);
}
