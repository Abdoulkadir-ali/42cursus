/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:32:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:46:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

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
	int	bpp;
	int	line_len;

	if (!init_window_main_image(win, win->mlx_ptr))
		return (0);
	win->gui_img.img = mlx_new_image(win->mlx_ptr, GUI_PANEL_WIDTH,
			win->height);
	if (!win->gui_img.img)
		return (0);
	win->gui_img.img_addr = mlx_get_data_addr(win->gui_img.img, &bpp, &line_len,
			&win->gui_img.img_endian);
	win->gui_img.img_bpp = (size_t)bpp;
	win->gui_img.img_line_len = (size_t)line_len;
	return (win->gui_img.img_addr != NULL);
}

int	handle_resize(t_events *events)
{
	t_resize_ctx	ctx;

	ctx.win = events->window;
	ctx.mlx = (t_mlx_ptr *)ctx.win->mlx_ptr;
	ctx.win_list = (t_mlx_win_list *)ctx.win->ptr;
	XGetWindowAttributes((Display *)ctx.mlx->display,
		(Window)ctx.win_list->window, &ctx.attrs);
	if ((size_t)ctx.attrs.width != ctx.win->width
		|| (size_t)ctx.attrs.height != ctx.win->height)
	{
		ctx.old_size = (t_vec2){ctx.win->width, ctx.win->height};
		ctx.new_size = (t_vec2){ctx.attrs.width, ctx.attrs.height};
		recenter_camera_on_resize(events->camera, ctx.old_size, ctx.new_size);
		ctx.win->width = ctx.attrs.width;
		ctx.win->height = ctx.attrs.height;
		free_buffers(ctx.win);
		if (!recreate_buffers(ctx.win))
			cleanup_and_exit(events);
		redraw(events);
	}
	return (0);
}
