/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:58:16 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 00:33:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_triangle_quad(t_graphics *g, int x, int y, int step)
{
	t_point	p1;
	t_point	p2;
	t_point	p3;
	t_point	p4;
	size_t	idx;
	size_t	next_row_idx;

	if (x + step >= (int)g->map->width || y + step >= (int)g->map->height)
		return ;
	idx = y * g->map->width + x;
	next_row_idx = (y + step) * g->map->width + x;
	
	p1 = get_cached_proj_fast(g, idx);
	p2 = get_cached_proj_fast(g, idx + step);
	p3 = get_cached_proj_fast(g, next_row_idx);
	p4 = get_cached_proj_fast(g, next_row_idx + step);
	
	if (!is_on_screen(p1.pos.x, p1.pos.y, g) && !is_on_screen(p2.pos.x, p2.pos.y, g)
		&& !is_on_screen(p3.pos.x, p3.pos.y, g) && !is_on_screen(p4.pos.x, p4.pos.y, g))
		return ;
	draw_quad_triangles(g, (t_quad_triangle){p1, p2, p3, p4});
}

void	draw_grid_row(t_graphics *g, int y, float lod_value)
{
	size_t	x;
	size_t	next_x;
	int		step_int;
	size_t	idx;
	size_t	row_base;
	size_t	total_points;

	x = 0;
	step_int = (int)lod_value;
	if (step_int < 1)
		step_int = 1;
	total_points = g->map->width * g->map->height;
	row_base = y * g->map->width;

	while (x < g->map->width)
	{
		idx = row_base + x;
		if (g->cache.points == NULL || idx >= total_points)
			break ;

		if (g->render_config.render_mode == RENDER_TRIANGLES
			|| (g->render_config.render_mode == RENDER_LINES && g->render_config.filled))
		{
			draw_triangle_quad(g, x, y, step_int);
			x += step_int;
			continue ;
		}
		
		next_x = x + step_int;
		if (next_x < g->map->width)
		{
			draw_segment(g, (t_draw_line_params){x, y,
					g->cache.points[idx], step_int}, 1);
		}
		if (y + step_int < (int)g->map->height)
		{
			draw_segment(g, (t_draw_line_params){x, y,
					g->cache.points[idx], step_int}, 0);
		}
		x += step_int;
	}
}
