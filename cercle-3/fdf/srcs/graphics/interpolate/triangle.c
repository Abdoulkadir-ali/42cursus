/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:23:31 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 13:27:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"


static int	interpolate_x(t_point p1, t_point p2, int y)
{
	double	t;

	if (p2.pos.y == p1.pos.y)
		return ((int)p1.pos.x);
	t = (y - p1.pos.y) / (p2.pos.y - p1.pos.y);
	return ((int)(p1.pos.x + t * (p2.pos.x - p1.pos.x)));
}

static float	interpolate_z(t_point p1, t_point p2, int y)
{
	double	t;

	if (p2.pos.y == p1.pos.y)
		return (p1.pos.z);
	t = (y - p1.pos.y) / (p2.pos.y - p1.pos.y);
	return (p1.pos.z + t * (p2.pos.z - p1.pos.z));
}

static int	interpolate_color_edge(t_point p1, t_point p2, int y)
{
	double	t;

	if (p2.pos.y == p1.pos.y)
		return (p1.color);
	t = (y - p1.pos.y) / (p2.pos.y - p1.pos.y);
	return (interpolate_color(p1.color, p2.color, t));
}

t_scanline_data	interpolate_triangle_scanline(t_triangle_interp interp)
{
	t_scanline_data	data;

	if (interp.y < (int)interp.triangle.p2.pos.y)
	{
		data.x1 = interpolate_x(interp.triangle.p1, interp.triangle.p3, interp.y);
		data.x2 = interpolate_x(interp.triangle.p1, interp.triangle.p2, interp.y);
		data.z1 = interpolate_z(interp.triangle.p1, interp.triangle.p3, interp.y);
		data.z2 = interpolate_z(interp.triangle.p1, interp.triangle.p2, interp.y);
		data.c1 = interpolate_color_edge(interp.triangle.p1, interp.triangle.p3, interp.y);
		data.c2 = interpolate_color_edge(interp.triangle.p1, interp.triangle.p2, interp.y);
	}
	else
	{
		data.x1 = interpolate_x(interp.triangle.p1, interp.triangle.p3, interp.y);
		data.x2 = interpolate_x(interp.triangle.p2, interp.triangle.p3, interp.y);
		data.z1 = interpolate_z(interp.triangle.p1, interp.triangle.p3, interp.y);
		data.z2 = interpolate_z(interp.triangle.p2, interp.triangle.p3, interp.y);
		data.c1 = interpolate_color_edge(interp.triangle.p1, interp.triangle.p3, interp.y);
		data.c2 = interpolate_color_edge(interp.triangle.p2, interp.triangle.p3, interp.y);
	}
	data.y = interp.y;
	return (data);
}
