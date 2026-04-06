/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 14:52:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	upscale_row(t_gui *gui, t_vec2i dst, double ry)
{
	t_vec2	src;
	double	step_x;
	int		dsw;

	src.y = ry;
	step_x = (double)gui->win.size.x / (double)gui->win.disp_size.x;
	dsw = gui->win.disp_size.x;
	src.x = 0;
	dst.x = 0;
	while (dst.x < dsw)
	{
		upscale_pixel(gui, dst, src);
		src.x += step_x;
		dst.x++;
	}
}

void	upscale_band(t_gui *gui, size_t y_start, size_t y_end)
{
	t_vec2i	dst;
	double	ry;
	double	step_y;

	step_y = (double)gui->win.size.y / (double)gui->win.disp_size.y;
	ry = (double)y_start * step_y;
	dst.y = y_start;
	dst.x = 0;
	while ((size_t)dst.y < y_end)
	{
		upscale_row(gui, dst, ry);
		ry += step_y;
		dst.y++;
	}
}

void	upscale_image(t_gui *gui)
{
	void	*dst;
	size_t	len;

	if (gui->win.size.x == gui->win.disp_size.x
		&& gui->win.size.y == gui->win.disp_size.y)
	{
		dst = gui->win.disp_addrs[gui->render.back_idx];
		len = gui->win.disp_size.y * gui->win.disp_line_len;
		ft_memcpy(dst, gui->win.addr, len);
		return ;
	}
	gui_parallel_task_worker(gui, TASK_UPSCALE);
}
