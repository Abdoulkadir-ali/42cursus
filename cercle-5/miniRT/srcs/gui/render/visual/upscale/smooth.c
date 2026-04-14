/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 01:35:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static uint32_t	blend3(uint32_t a, uint32_t b, uint32_t c)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	bv;

	r = (((a >> 16) & 0xFF) + ((b >> 16) & 0xFF) + ((c >> 16) & 0xFF)) / 3;
	g = (((a >> 8) & 0xFF) + ((b >> 8) & 0xFF) + ((c >> 8) & 0xFF)) / 3;
	bv = ((a & 0xFF) + (b & 0xFF) + (c & 0xFF)) / 3;
	return ((r << 16) | (g << 8) | bv);
}

static uint32_t	sample_clamp(const uint32_t *buf, t_vec2i p, t_vec2i sz)
{
	if (p.x < 0)
		p.x = 0;
	if (p.x >= sz.x)
		p.x = sz.x - 1;
	if (p.y < 0)
		p.y = 0;
	if (p.y >= sz.y)
		p.y = sz.y - 1;
	return (buf[p.y * sz.x + p.x]);
}

static void	smooth_row(t_gui *gui, t_vec2i sz, int y, uint32_t *buf)
{
	uint32_t	tmp[RENDER_W];
	int			x;

	(void)gui;
	x = 0;
	while (x < sz.x)
	{
		tmp[x] = blend3(sample_clamp(buf, (t_vec2i){x - 1, y}, sz),
				sample_clamp(buf, (t_vec2i){x, y}, sz),
				sample_clamp(buf, (t_vec2i){x + 1, y}, sz));
		x++;
	}
	x = 0;
	while (x < sz.x)
	{
		buf[y * sz.x + x] = blend3(sample_clamp(tmp, (t_vec2i){x, 0},
					(t_vec2i){sz.x, 1}),
				sample_clamp(buf, (t_vec2i){x, y - 1}, sz),
				sample_clamp(buf, (t_vec2i){x, y + 1}, sz));
		x++;
	}
}

void	smooth_render_band(t_gui *gui, size_t y_start, size_t y_end)
{
	t_vec2i	sz;
	int		y;

	if (gui->render.scale < 2)
		return ;
	sz = (t_vec2i){(int)gui->win.size.x, (int)gui->win.size.y};
	y = (int)y_start;
	while (y < (int)y_end)
		smooth_row(gui, sz, y++, (uint32_t *)gui->win.addr);
}

void	smooth_render(t_gui *gui)
{
	if (gui->render.scale < 2 || gui->opts.taa)
		return ;
	gui_parallel_task_worker(gui, TASK_BLUR);
}
