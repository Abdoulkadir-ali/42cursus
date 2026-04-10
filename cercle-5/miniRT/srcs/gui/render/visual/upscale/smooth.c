/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smooth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/10 00:56:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
** 3x3 box blur on the low-res render buffer.
** Reads from render_pixels (via win.addr), writes back in-place row by row.
** Only the current render dimensions (win.size) are touched — not the full
** disp_size allocation — so it is safe at any adaptive scale level.
*/
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

static uint32_t	sample_clamp(const uint32_t *buf, int x, int y, int w, int h)
{
	if (x < 0)
		x = 0;
	if (x >= w)
		x = w - 1;
	if (y < 0)
		y = 0;
	if (y >= h)
		y = h - 1;
	return (buf[y * w + x]);
}

/*
** Horizontal 1D box pass into a scratch row stored in a static thread-local
** buffer.  Then the vertical pass reads from the original buffer.
** We do a simple separable 3-tap box (1/3, 1/3, 1/3) — fast and effective.
*/
void	smooth_render_band(t_gui *gui, size_t y_start, size_t y_end)
{
	uint32_t	*buf;
	uint32_t	tmp[RENDER_W];
	uint32_t	h_px;
	int			w;
	int			h;
	int			x;
	int			y;

	if (gui->render.scale < 2)
		return ;
	buf = (uint32_t *)gui->win.addr;
	w = (int)gui->win.size.x;
	h = (int)gui->win.size.y;
	y = (int)y_start;
	while (y < (int)y_end)
	{
		x = 0;
		while (x < w)
		{
			h_px = blend3(
				sample_clamp(buf, x - 1, y, w, h),
				sample_clamp(buf, x, y, w, h),
				sample_clamp(buf, x + 1, y, w, h));
			tmp[x] = h_px;
			x++;
		}
		x = 0;
		while (x < w)
		{
			buf[y * w + x] = blend3(
				sample_clamp((uint32_t *)tmp, x, 0, w, 1),
				buf[((y > 0 ? y - 1 : 0)) * w + x],
				buf[((y < h - 1 ? y + 1 : h - 1)) * w + x]);
			x++;
		}
		y++;
	}
}

void	smooth_render(t_gui *gui)
{
	if (gui->render.scale < 2)
		return ;
	gui_parallel_task_worker(gui, TASK_BLUR);
}
