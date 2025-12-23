/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 20:03:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

void	draw_filled_triangle(t_graphics *g, t_triangle t)
{
	double	ratio;
	t_point	p4;

	if (g->render_config.use_depth_culling && is_backface(t.p1, t.p2, t.p3))
		return ;
	if (t.p1.pos.y > t.p2.pos.y)
		swap_points(&t.p1, &t.p2);
	if (t.p1.pos.y > t.p3.pos.y)
		swap_points(&t.p1, &t.p3);
	if (t.p2.pos.y > t.p3.pos.y)
		swap_points(&t.p2, &t.p3);
	if ((int)t.p2.pos.y == (int)t.p3.pos.y)
		rasterize_flat_bottom(g, t.p1, t.p2, t.p3);
	else if ((int)t.p1.pos.y == (int)t.p2.pos.y)
		rasterize_flat_top(g, t.p1, t.p2, t.p3);
	else
	{
		ratio = (t.p2.pos.y - t.p1.pos.y) / (t.p3.pos.y - t.p1.pos.y);
		p4.pos.x = t.p1.pos.x + (t.p3.pos.x - t.p1.pos.x) * ratio;
		p4.pos.y = t.p2.pos.y;
		p4.pos.z = t.p1.pos.z + (t.p3.pos.z - t.p1.pos.z) * ratio;
		p4.color = interpolate_color(t.p1.color, t.p3.color, ratio);
		rasterize_flat_bottom(g, t.p1, t.p2, p4);
		rasterize_flat_top(g, t.p2, p4, t.p3);
	}
}

void	draw_wireframe_triangle(t_graphics *g, t_triangle t)
{
	draw_line(g, t.p1, t.p2);
	draw_line(g, t.p2, t.p3);
	draw_line(g, t.p3, t.p1);
}

void	draw_quad_triangles(t_graphics *g, t_quad_triangle quad)
{
	if (g->render_config.filled)
	{
		draw_filled_triangle(g, (t_triangle){quad.p1, quad.p2, quad.p3});
		draw_filled_triangle(g, (t_triangle){quad.p2, quad.p4, quad.p3});
	}
	else
	{
		draw_wireframe_triangle(g, (t_triangle){quad.p1, quad.p2, quad.p3});
		draw_wireframe_triangle(g, (t_triangle){quad.p2, quad.p4, quad.p3});
	}
}

void	draw_triangle(t_graphics *g, t_point p1, t_point p2, t_point p3)
{
	if (g->render_config.filled)
		draw_filled_triangle(g, (t_triangle){p1, p2, p3});
	else
		draw_wireframe_triangle(g, (t_triangle){p1, p2, p3});
}
