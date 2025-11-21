/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 21:40:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* lines.c - Fast Integer Bresenham with Z-Interpolation                      */
/* ************************************************************************** */

#include "graphics.h"
#include "color.h"
#include <math.h>

/* Inline fast pixel put with optional z-buffer test. This minimizes per-pixel
 * function-call overhead. The caller must ensure coordinates are reasonable
 * (we still check bounds per pixel once). */
static inline void fast_put_pixel(t_graphics *g, int x, int y, float z, int color)
{
	t_window *w = g->window;
	unsigned int *dst;
	int index;

	if (x < 0 || x >= w->width || y < 0 || y >= w->height)
		return ;

	if (g->render_config.use_depth_culling && w->z_buffer)
	{
		index = y * w->width + x;
		if (z >= w->z_buffer[index])
			return ;
		w->z_buffer[index] = z;
	}

	dst = (unsigned int *)(w->main_img.img_addr + y * w->main_img.img_line_len + x * (w->main_img.img_bpp / 8));
	*dst = (unsigned int)color;
}

/* Fast integer Bresenham with incremental color & z interpolation */
void draw_line(t_graphics *g, t_point start, t_point end)
{
	int x0 = (int)lround(start.pos.x);
	int y0 = (int)lround(start.pos.y);
	int x1 = (int)lround(end.pos.x);
	int y1 = (int)lround(end.pos.y);
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	int steps = (dx > dy) ? dx : dy;
	int i = 0;

	double zr = start.pos.z;
	double zr_step = 0.0;
	if (steps > 0)
		zr_step = (end.pos.z - start.pos.z) / (double)steps;

	/* incremental color components (wrap behavior) */
	int sr = get_red(start.color);
	int sgc = get_green(start.color);
	int sb = get_blue(start.color);
	int er = get_red(end.color);
	int eg = get_green(end.color);
	int eb = get_blue(end.color);
	double dr = 0.0, dg = 0.0, db = 0.0;
	double cr = sr, cg = sgc, cb = sb;
	if (steps > 0)
	{
		dr = (double)(er - sr) / (double)steps;
		dg = (double)(eg - sgc) / (double)steps;
		db = (double)(eb - sb) / (double)steps;
	}

	int x = x0;
	int y = y0;

	while (1)
	{
		/* compose current color (wrap via & 0xFF to avoid function call) */
		int ir = ((int)cr) & 0xFF;
		int ig = ((int)cg) & 0xFF;
		int ib = ((int)cb) & 0xFF;
		int color = (ir << 16) | (ig << 8) | ib;

		/* apply camera color shift by wrapping components */
		if (g->camera->color_shift.x || g->camera->color_shift.y || g->camera->color_shift.z)
		{
			ir = (ir + g->camera->color_shift.x) & 0xFF;
			ig = (ig + g->camera->color_shift.y) & 0xFF;
			ib = (ib + g->camera->color_shift.z) & 0xFF;
			color = (ir << 16) | (ig << 8) | ib;
		}

		fast_put_pixel(g, x, y, (float)zr, color);

		if (x == x1 && y == y1)
			break;

		int e2 = 2 * err;
		if (e2 > -dy) { err -= dy; x += sx; }
		if (e2 < dx)  { err += dx; y += sy; }

		/* advance interpolants */
		zr += zr_step;
		cr += dr; cg += dg; cb += db;
		i++;
	}
}