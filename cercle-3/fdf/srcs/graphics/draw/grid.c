/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 19:41:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "graphics.h"
#include <pthread.h>

#define NUM_THREADS 4

static void	draw_horizontal_line(t_graphics *g, int x, int y, t_point p1,
		int step)
{
	t_point	p0;
	t_point	p2;
	t_point	p3;
	int		next_x;
	int		prev_x;

	next_x = x + step;
	if (next_x >= g->map->width
		|| !is_point_visible(g->map->points.pos[y][next_x], g))
		return ;
	p2 = project_point(g->map->points.pos[y][next_x],
			g->map->points.color[y][next_x], g->camera, g->map->z_divisor);
	if (!should_draw_line(p1, p2, g))
		return ;
	/* debug prints removed */
	if (g->render_config.render_mode == RENDER_SPLINES)
	{
		prev_x = x - step;
		if (prev_x >= 0)
			p0 = project_point(g->map->points.pos[y][prev_x],
					g->map->points.color[y][prev_x], g->camera,
					g->map->z_divisor);
		else
			p0 = p1;
		if (next_x + step < g->map->width)
			p3 = project_point(g->map->points.pos[y][next_x + step],
					g->map->points.color[y][next_x + step], g->camera,
					g->map->z_divisor);
		else
			p3 = p2;
		draw_spline_segment(g, (t_spline){p0, p1, p2, p3}, g->camera->spline_segments);
	}
	else if (g->render_config.render_mode == RENDER_LINES)
		draw_line(g, p1, p2);
}

static void	draw_vertical_line(t_graphics *g, int x, int y, t_point p1,
		int step)
{
	t_point	p0;
	t_point	p2;
	t_point	p3;
	int		next_y;
	int		prev_y;

	next_y = y + step;
	if (next_y >= g->map->height
		|| !is_point_visible(g->map->points.pos[next_y][x], g))
		return ;
	p2 = project_point(g->map->points.pos[next_y][x],
			g->map->points.color[next_y][x], g->camera, g->map->z_divisor);
	if (!should_draw_line(p1, p2, g))
		return ;
	if (g->render_config.render_mode == RENDER_SPLINES)
	{
		prev_y = y - step;
		if (prev_y >= 0)
			p0 = project_point(g->map->points.pos[prev_y][x],
					g->map->points.color[prev_y][x], g->camera,
					g->map->z_divisor);
		else
			p0 = p1;
		if (next_y + step < g->map->height)
			p3 = project_point(g->map->points.pos[next_y + step][x],
					g->map->points.color[next_y + step][x], g->camera,
					g->map->z_divisor);
		else
			p3 = p2;
		draw_spline_segment(g, (t_spline){p0, p1, p2, p3}, g->camera->spline_segments);
	}
	else if (g->render_config.render_mode == RENDER_LINES)
		draw_line(g, p1, p2);
}

static void	draw_triangle_quad(t_graphics *g, int x, int y, int step)
{
	t_point	p1;
	t_point	p2;
	t_point	p3;
	t_point	p4;

	if (x + step >= g->map->width || y + step >= g->map->height)
		return ;
	p1 = project_point(g->map->points.pos[y][x], g->map->points.color[y][x],
			g->camera, g->map->z_divisor);
	p2 = project_point(g->map->points.pos[y][x + step],
			g->map->points.color[y][x + step], g->camera, g->map->z_divisor);
	p3 = project_point(g->map->points.pos[y + step][x], g->map->points.color[y
			+ step][x], g->camera, g->map->z_divisor);
	p4 = project_point(g->map->points.pos[y + step][x + step],
			g->map->points.color[y + step][x + step], g->camera,
			g->map->z_divisor);
	draw_quad_triangles(g, (t_quad_triangle){p1, p2, p3, p4});
}

static void	draw_grid_section(t_graphics *g, int start_y, int end_y, int step)
{
	int		x;
	int		y;
	t_point	p1;

	/* debug prints removed */

	y = start_y;
	while (y < end_y)
	{
		/* debug prints removed */
		x = 0;
		while (x < g->map->width)
		{
			/* debug prints removed */
			/* debug prints removed */
			if (g->render_config.render_mode == RENDER_TRIANGLES)
			{
				draw_triangle_quad(g, x, y, step);
				x += step;
				continue ;
			}
			if (!is_point_visible(g->map->points.pos[y][x], g))
			{
				x += step;
				continue ;
			}
			p1 = project_point(g->map->points.pos[y][x],
					g->map->points.color[y][x], g->camera, g->map->z_divisor);
			draw_horizontal_line(g, x, y, p1, step);
			draw_vertical_line(g, x, y, p1, step);
			x += step;
		}
		y += step;
	}
	/* debug prints removed */
}

void	draw_grid(t_graphics *g)
{
	int				step;

	step = g->render_config.lod_level;
	draw_grid_section(g, 0, g->map->height, step);
}