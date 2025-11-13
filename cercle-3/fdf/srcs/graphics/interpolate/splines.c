/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 13:32:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

double	catmull_rom_interpolate(t_vec4d c, double t)
{
	double	t2;
	double	t3;
	double	result;

	t2 = t * t;
	t3 = t2 * t;
	result = 0.5 * ((2.0 * c.y) + (-c.x + c.z) * t + (2.0 * c.x - 5.0 * c.y
				+ 4.0 * c.z - c.w) * t2 + (-c.x + 3.0 * c.y - 3.0 * c.z + c.w)
			* t3);
	return (result);
}

t_point	catmull_rom_point(t_spline spline, double t)
{
	t_point	result;
	t_vec4d	cx;
	t_vec4d	cy;
	t_vec4d	cz;

	cx = (t_vec4d){spline.p0.pos.x, spline.p1.pos.x, spline.p2.pos.x,
		spline.p3.pos.x};
	cy = (t_vec4d){spline.p0.pos.y, spline.p1.pos.y, spline.p2.pos.y,
		spline.p3.pos.y};
	cz = (t_vec4d){spline.p0.pos.z, spline.p1.pos.z, spline.p2.pos.z,
		spline.p3.pos.z};
	result.pos.x = catmull_rom_interpolate(cx, t);
	result.pos.y = catmull_rom_interpolate(cy, t);
	result.pos.z = catmull_rom_interpolate(cz, t);
	result.color = spline.p1.color;
	return (result);
}

t_point	lerp_point(t_point p1, t_point p2, double t)
{
	t_point	result;

	result.pos.x = p1.pos.x + (p2.pos.x - p1.pos.x) * t;
	result.pos.y = p1.pos.y + (p2.pos.y - p1.pos.y) * t;
	result.pos.z = p1.pos.z + (p2.pos.z - p1.pos.z) * t;
	result.color = interpolate_color(p1.color, p2.color, t);
	return (result);
}