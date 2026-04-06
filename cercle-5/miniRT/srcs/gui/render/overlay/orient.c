/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orient.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 15:41:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	orient_put_pixel(t_gui *gui, t_vec2i p, int col)
{
	int			w;
	int			h;
	uint32_t	*dst;

	w = gui->win.disp_size.x;
	h = gui->win.disp_size.y;
	if (p.x < 0 || p.y < 0 || p.x >= w || p.y >= h)
		return ;
	dst = (uint32_t *)(gui->win.disp_addrs[gui->render.back_idx]
			+ (p.y * gui->win.disp_line_len
				+ p.x * (gui->win.disp_bpp / 8)));
	*dst = color_blend(*dst, col, 0.9f);
}

static void	orient_line_step(t_vec2i *a, t_vec2i s, t_vec2i d, int *err)
{
	int	e2;

	e2 = 2 * *err;
	if (e2 >= d.y)
	{
		*err += d.y;
		a->x += s.x;
	}
	if (e2 <= d.x)
	{
		*err += d.x;
		a->y += s.y;
	}
}

static void	orient_line(t_gui *gui, t_vec2i a, t_vec2i b, int col)
{
	t_vec2i	s;
	t_vec2i	d;
	int		err;

	d.x = abs(b.x - a.x);
	d.y = -abs(b.y - a.y);
	s.x = -1;
	if (a.x < b.x)
		s.x = 1;
	s.y = -1;
	if (a.y < b.y)
		s.y = 1;
	err = d.x + d.y;
	while (1)
	{
		orient_put_pixel(gui, a, col);
		if (a.x == b.x && a.y == b.y)
			break ;
		orient_line_step(&a, s, d, &err);
	}
}

static void	orient_axis(t_gui *gui, t_vec2i c, t_vec3 v, int col)
{
	t_vec2i	e;
	t_vec2i	tip;
	int		len;
	int		tiplen;

	len = (gui->win.disp_size.y / 24);
	tiplen = (gui->win.disp_size.y / 192);
	e = vec2i(c.x + (v.x * len), c.y - (v.y * len));
	tip = vec2i(e.x - (v.x * tiplen) - (v.y * tiplen),
			e.y + (v.y * tiplen) - (v.x * tiplen));
	orient_line(gui, c, e, col);
	orient_line(gui, e, tip, col);
}

void	draw_ui_orient(t_gui *gui)
{
	t_vec2i	c;
	int		off;

	off = (gui->win.disp_size.y / 14);
	c = vec2i(gui->win.disp_size.x - off, gui->win.disp_size.y - off);
	orient_axis(gui, c, gui->cam_ctrl.transform.right, AXIS_COL_X);
	orient_axis(gui, c, gui->cam_ctrl.transform.up, AXIS_COL_Y);
	orient_axis(gui, c, gui->cam_ctrl.transform.forward, AXIS_COL_Z);
}
