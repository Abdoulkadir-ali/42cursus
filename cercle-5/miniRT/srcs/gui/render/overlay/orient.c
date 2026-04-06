/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orient.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 02:52:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	orient_put_pixel(t_gui *gui, t_vec2i p, int col)
{
	size_t	w;
	size_t	h;
	size_t	*dst;

	w = gui->win.disp_size.x;
	h = gui->win.disp_size.y;
	if (p.x >= w || p.y >= h)
		return ;
	dst = (size_t *)(gui->win.disp_addrs[gui->render.back_idx]
			+ (p.y * gui->win.disp_line_len
				+ p.x * (gui->win.disp_bpp / 8)));
	*dst = color_blend(*dst, col, 0.9f);
}

static void	orient_line_step(t_vec2i *a, t_vec2i b, t_vec2i s, int *err)
{
	int	e2;
	int	dx;
	int	dy;

	dx = abs((int)b.x - (int)a->x);
	dy = -abs((int)b.y - (int)a->y);
	e2 = 2 * *err;
	if (e2 >= dy)
	{
		*err += dy;
		a->x += s.x;
	}
	if (e2 <= dx)
	{
		*err += dx;
		a->y += s.y;
	}
}

static void	orient_line(t_gui *gui, t_vec2i a, t_vec2i b, int col)
{
	t_vec2i	s;
	int		err;

	s.x = -1;
	if (a.x < b.x)
		s.x = 1;
	s.y = -1;
	if (a.y < b.y)
		s.y = 1;
	err = abs((int)b.x - (int)a.x) - abs((int)b.y - (int)a.y);
	while (1)
	{
		orient_put_pixel(gui, a, col);
		if (a.x == b.x && a.y == b.y)
			break ;
		orient_line_step(&a, b, s, &err);
	}
}

static void	orient_axis(t_gui *gui, t_vec2i c, t_vec3 v, int col)
{
	t_vec2i	e;
	t_vec2i	tip;
	int		len;
	int		tiplen;

	len = (int)(gui->win.disp_size.y / 24);
	tiplen = (int)(gui->win.disp_size.y / 192);
	e = vec2i(c.x + (int)(v.x * len), c.y - (int)(v.y * len));
	tip = vec2i(e.x - (int)(v.x * tiplen) - (int)(v.y * tiplen),
			e.y + (int)(v.y * tiplen) - (int)(v.x * tiplen));
	orient_line(gui, c, e, col);
	orient_line(gui, e, tip, col);
}

void	draw_ui_orient(t_gui *gui)
{
	t_vec2i	c;
	int		off;

	off = (int)(gui->win.disp_size.y / 14);
	c = vec2i(gui->win.disp_size.x - off, gui->win.disp_size.y - off);
	orient_axis(gui, c, gui->cam_ctrl.transform.right, AXIS_COL_X);
	orient_axis(gui, c, gui->cam_ctrl.transform.up, AXIS_COL_Y);
	orient_axis(gui, c, gui->cam_ctrl.transform.forward, AXIS_COL_Z);
}
