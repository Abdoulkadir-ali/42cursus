/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upscale.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 10:28:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
** Depth-aware bilinear upscale from render buffer to display image.
** Neighbours with a depth discontinuity (>15%) are excluded so edges
** are not blurred across object boundaries.
**
** Hot-path optimisations vs. the naive version:
**   - ry/y0/y1/fy and the four render row-pointers are hoisted to outer loop
**   - rx advances incrementally (step_x added per pixel, no per-pixel multiply)
**   - ify = 1-fy and inv_wt = 1/wt remove per-pixel division
**   - bilerp_colors is inlined (no function-call overhead, better auto-vec)
*/

static uint32_t	bilerp_pixel(uint32_t c00, uint32_t c10,
	uint32_t c01, uint32_t c11,
	float w00, float w10, float w01, float w11)
{
	float		wt;
	float		inv;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	wt = w00 + w10 + w01 + w11;
	if (wt < 1e-6f)
		return (c00);
	inv = 1.0f / wt;
	r = (uint32_t)((w00 * ((c00 >> 16) & 0xFF) + w10 * ((c10 >> 16) & 0xFF)
				+ w01 * ((c01 >> 16) & 0xFF) + w11 * ((c11 >> 16) & 0xFF))
			* inv);
	g = (uint32_t)((w00 * ((c00 >> 8) & 0xFF) + w10 * ((c10 >> 8) & 0xFF)
				+ w01 * ((c01 >> 8) & 0xFF) + w11 * ((c11 >> 8) & 0xFF))
			* inv);
	b = (uint32_t)((w00 * (c00 & 0xFF) + w10 * (c10 & 0xFF)
				+ w01 * (c01 & 0xFF) + w11 * (c11 & 0xFF)) * inv);
	return ((r << 16) | (g << 8) | b);
}

void	upscale_band(t_gui *gui, size_t y_start, size_t y_end)
{
	size_t		rw;
	size_t		rh;
	size_t		dw;
	float		step_x;
	float		step_y;
	float		ry;
	size_t		dy;
	size_t		dx;
	int			y0;
	int			y1;
	float		fy;
	float		rx;
	int			x0;
	int			x1;
	float		fx;
	float		dref;
	float		thresh;
	float		ify;
	float		*depy0;
	float		*depy1;
	uint32_t	*srcy0;
	uint32_t	*srcy1;
	uint32_t	*dst;
	uint32_t	*src;
	float		*dep;

	src = (uint32_t *)gui->win.addr;
	dep = gui->render.depth_buf;
	rw = (size_t)gui->win.size.x;
	rh = (size_t)gui->win.size.y;
	dw = (size_t)gui->win.disp_size.x;
	step_x = (float)rw / (float)gui->win.disp_size.x;
	step_y = (float)rh / (float)gui->win.disp_size.y;
	ry = (y_start + 0.5f) * step_y - 0.5f;
	dy = y_start;
	while (dy < y_end)
	{
		y0 = (int)ry;
		if (y0 < 0)
			y0 = 0;
		if (y0 >= (int)rh - 1)
			y0 = (int)rh - 2;
		if (y0 < 0)
			y0 = 0;
		y1 = y0 + 1;
		fy = ry - (float)y0;
		if (fy < 0.0f)
			fy = 0.0f;
		ify = 1.0f - fy;
		depy0 = dep + y0 * rw;
		depy1 = dep + y1 * rw;
		srcy0 = src + y0 * rw;
		srcy1 = src + y1 * rw;
		dst = (uint32_t *)(gui->win.disp_addr + dy * gui->win.disp_line_len);
		rx = 0.5f * step_x - 0.5f;
		dx = 0;
		while (dx < dw)
		{
			x0 = (int)rx;
			if (x0 < 0)
				x0 = 0;
			if (x0 >= (int)rw - 1)
				x0 = (int)rw - 2;
			if (x0 < 0)
				x0 = 0;
			x1 = x0 + 1;
			fx = rx - (float)x0;
			if (fx < 0.0f)
				fx = 0.0f;
			dref = depy0[x0];
			thresh = (dref < 1e28f ? fmaxf(dref * 0.15f, 0.5f) : 1e30f);
			dst[dx] = bilerp_pixel(srcy0[x0], srcy0[x1], srcy1[x0], srcy1[x1],
					(1.0f - fx) * ify,
					(fabsf(depy0[x1] - dref) < thresh) ? fx * ify : 0.0f,
					(fabsf(depy1[x0] - dref) < thresh) ? (1.0f - fx) * fy : 0.0f,
					(fabsf(depy1[x1] - dref) < thresh) ? fx * fy : 0.0f);
			rx += step_x;
			dx++;
		}
		ry += step_y;
		dy++;
	}
}

void	upscale_image(t_gui *gui)
{
	if (gui->win.size.x == gui->win.disp_size.x
		&& gui->win.size.y == gui->win.disp_size.y)
	{
		ft_memcpy(gui->win.disp_addr, gui->win.addr, (size_t)gui->win.disp_size.y
			* gui->win.disp_line_len);
		return ;
	}
	gui_parallel_task_worker(gui, TASK_UPSCALE);
}
