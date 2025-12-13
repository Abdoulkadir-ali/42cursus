/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:58:16 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 13:13:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_triangle_quad(t_graphics *g, int x, int y, int step)
{
	t_point	p1;
	t_point	p2;
	t_point	p3;
	t_point	p4;

	if (x + step >= g->map->width || y + step >= g->map->height)
		return ;
	p1 = get_cached_proj(g, x, y);
	p2 = get_cached_proj(g, x + step, y);
	p3 = get_cached_proj(g, x, y + step);
	p4 = get_cached_proj(g, x + step, y + step);
	draw_quad_triangles(g, (t_quad_triangle){p1, p2, p3, p4});
}

void	draw_grid_row(t_graphics *g, int y, int step)
{
	int		x;
	t_point	p1;

	x = 0;
	while (x < g->map->width)
	{
		if (g->render_config.render_mode == RENDER_TRIANGLES)
		{
			draw_triangle_quad(g, x, y, step);
			x += step;
			continue ;
		}
		p1 = get_cached_proj(g, x, y);
		if (!is_point_visible(g->map->points.pos[y * g->map->width + x], g))
		{
			x += step;
			continue ;
		}
		draw_segment(g, (t_draw_line_params){x, y, p1, step}, 1);
		draw_segment(g, (t_draw_line_params){x, y, p1, step}, 0);
		x += step;
	}
}
