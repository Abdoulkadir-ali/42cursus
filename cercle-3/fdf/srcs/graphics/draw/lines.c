/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 21:05:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* lines.c - Fast Integer Bresenham with Z-Interpolation                      */
/* ************************************************************************** */

#include "graphics.h"
#include "color.h"
#include <math.h>
#include <limits.h>

static int safe_to_int(double d)
{
	if (!isfinite(d))
		return 0;
	if (d > (double)(INT_MAX - 4))
		return INT_MAX - 4;
	if (d < (double)(INT_MIN + 4))
		return INT_MIN + 4;
	return (int)lround(d);
}

/* Frustum culling: quickly reject lines that are fully off-screen or absurdly long */
static int is_line_visible(t_point s, t_point e, t_graphics *g)
{
	int sx = safe_to_int(s.pos.x);
	int sy = safe_to_int(s.pos.y);
	int ex = safe_to_int(e.pos.x);
	int ey = safe_to_int(e.pos.y);

	/* both left or both right */
	if (sx < 0 && ex < 0)
		return 0;
	if (sx >= g->window->width && ex >= g->window->width)
		return 0;
	/* both above or both below */
	if (sy < 0 && ey < 0)
		return 0;
	if (sy >= g->window->height && ey >= g->window->height)
		return 0;

	/* extremely long lines are likely invalid or caused by overflow/wrap */
	if (abs(ex - sx) > 50000 || abs(ey - sy) > 50000)
		return 0;

	return 1;
}

typedef struct s_line_vars {
	int     dx;
	int     dy;
	int     sx;
	int     sy;
	int     err;
	double  z;
	double  z_inc;
	double  current_dist;
	double  dist_inc;
} t_line_vars;

void    draw_line(t_graphics *g, t_point start, t_point end)
{
	t_line_vars v;
	int         e2;
	int         total_steps;

	/* 1. Safe integer coordinates (avoid UB when values are huge/NaN) */
	int xi = safe_to_int(start.pos.x);
	int yi = safe_to_int(start.pos.y);
	int xj = safe_to_int(end.pos.x);
	int yj = safe_to_int(end.pos.y);
	/* Cull lines that are fully off-screen or absurdly long */
	if (!is_line_visible(start, end, g))
		return ;

	/* 1. Setup Integer Bresenham */
	v.dx = abs(xj - xi);
	v.dy = abs(yj - yi);
	v.sx = (xi < xj) ? 1 : -1;
	v.sy = (yi < yj) ? 1 : -1;
	v.err = v.dx - v.dy;

	/* 2. Setup Fast Interpolation (Pre-calculate steps) */
	total_steps = (v.dx > v.dy) ? v.dx : v.dy;
	v.z = start.pos.z;
	v.z_inc = 0;
	v.current_dist = 0;
	v.dist_inc = 0;

	if (total_steps > 0)
	{
		v.z_inc = (end.pos.z - start.pos.z) / (double)total_steps;
		v.dist_inc = 1.0 / (double)total_steps;
	}

	/* 3. Draw Loop (operate on safe ints) */
	int step = 0;
	int x = xi;
	int y = yi;
	while (1)
	{
		if (is_visible(x, y, g))
		{
			/* compute interpolated color using pre-calculated ratio (0.0 to 1.0) */
			int color = interpolate_color(start.color, end.color, v.current_dist);
			if (g->camera->color_shift.x || g->camera->color_shift.y || g->camera->color_shift.z)
				color = shift_color(color, g->camera->color_shift.x, g->camera->color_shift.z, g->camera->color_shift.y);
			img_pixel_put_with_z(g, x, y, (float)v.z, color);
		}

		if (x == xj && y == yj)
			break ;

		/* Update Interpolators */
		v.z += v.z_inc;
		v.current_dist += v.dist_inc;

		/* Standard Bresenham Step */
		e2 = 2 * v.err;
		if (e2 > -v.dy) { v.err -= v.dy; x += v.sx; }
		if (e2 < v.dx)  { v.err += v.dx; y += v.sy; }
		step++;
	}
}