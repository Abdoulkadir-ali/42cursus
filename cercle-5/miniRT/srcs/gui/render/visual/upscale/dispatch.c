/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 02:56:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	upscale_row(t_gui *gui, size_t dy, float ry, size_t dims[2])
{
	size_t	dx;
	t_vec2i	dxy;
	t_vec2	rxy;

	dxy.y = (int)dy;
	rxy.y = ry;
	dx = -1;
	while (++dx < (size_t)gui->win.disp_size.x)
	{
		dxy.x = (int)dx;
		rxy.x = (double)dx * ((double)dims[0] / (double)gui->win.disp_size.x);
		upscale_pixel(gui, dxy, rxy, dims);
	}
}

void	upscale_band(t_gui *gui, size_t y_start, size_t y_end)
{
	size_t	dims[2];
	size_t	dy;
	float	step_y;

	dims[0] = (size_t)gui->win.size.x;
	dims[1] = (size_t)gui->win.size.y;
	step_y = (float)dims[1] / (float)gui->win.disp_size.y;
	dy = y_start;
	while (dy < y_end)
	{
		upscale_row(gui, dy, (float)dy * step_y, dims);
		dy++;
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
		len = (size_t)gui->win.disp_size.y * gui->win.disp_line_len;
		ft_memcpy(dst, gui->win.addr, len);
		return ;
	}
	gui_parallel_task_worker(gui, TASK_UPSCALE);
}
