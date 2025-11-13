/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 15:21:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	swap_point(t_point *a, t_point *b)
{
	t_point	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	draw_filled_triangle(t_graphics *g, t_triangle triangle)
{
	int				y;
	int				y_max;
	t_scanline_data	data;

	if (triangle.p1.pos.y > triangle.p2.pos.y)
		swap_point(&triangle.p1, &triangle.p2);
	if (triangle.p2.pos.y > triangle.p3.pos.y)
		swap_point(&triangle.p2, &triangle.p3);
	if (triangle.p1.pos.y > triangle.p2.pos.y)
		swap_point(&triangle.p1, &triangle.p2);
	y = (int)triangle.p1.pos.y;
	y_max = (int)triangle.p3.pos.y;
	if (y < -10000 || y > 10000 || y_max < -10000 || y_max > 10000)
		return ;
	if (y_max - y > g->window->height * 2)
		return ;
	while (y <= y_max)
	{
		t_triangle_interp	interp;

		interp.triangle = triangle;
		interp.y = y;
		data = interpolate_triangle_scanline(interp);
		draw_horizontal_scanline_z(g, data);
		y++;
	}
}

void	draw_wireframe_triangle(t_graphics *g, t_triangle triangle)
{
	draw_line(g, triangle.p1, triangle.p2);
	draw_line(g, triangle.p2, triangle.p3);
	draw_line(g, triangle.p3, triangle.p1);
}

void	draw_quad_triangles(t_graphics *g, t_quad_triangle quad)
{
	if (g->render_config.fill_triangles)
	{
		t_triangle t1 = {quad.p1, quad.p2, quad.p3};
		t_triangle t2 = {quad.p2, quad.p4, quad.p3};
		draw_filled_triangle(g, t1);
		draw_filled_triangle(g, t2);
	}
	else
	{
		t_triangle t1 = {quad.p1, quad.p2, quad.p3};
		t_triangle t2 = {quad.p2, quad.p4, quad.p3};
		draw_wireframe_triangle(g, t1);
		draw_wireframe_triangle(g, t2);
	}
}