/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 15:03:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_point	catmull_rom_point(t_spline spline, double t)
{
	double	t2;
	double	t3;
	t_vec3d	p;
	int		color;

	t2 = t * t;
	t3 = t2 * t;
	p.x = 0.5 * ((-t3 + 2 * t2 - t) * spline.p0.pos.x
			+ (3 * t3 - 5 * t2 + 2) * spline.p1.pos.x
			+ (-3 * t3 + 4 * t2 + t) * spline.p2.pos.x
			+ (t3 - t2) * spline.p3.pos.x);
	p.y = 0.5 * ((-t3 + 2 * t2 - t) * spline.p0.pos.y
			+ (3 * t3 - 5 * t2 + 2) * spline.p1.pos.y
			+ (-3 * t3 + 4 * t2 + t) * spline.p2.pos.y
			+ (t3 - t2) * spline.p3.pos.y);
	p.z = 0.5 * ((-t3 + 2 * t2 - t) * spline.p0.pos.z
			+ (3 * t3 - 5 * t2 + 2) * spline.p1.pos.z
			+ (-3 * t3 + 4 * t2 + t) * spline.p2.pos.z
			+ (t3 - t2) * spline.p3.pos.z);
	color = interpolate_color(spline.p1.color, spline.p2.color, t);
	return ((t_point){p, color});
}

void	draw_spline_segment(t_graphics *g, t_spline spline, int segments)
{
	int		i;
	double	t;
	double	step;
	t_point	curr;
	t_point	next;

	if (segments < 2)
		segments = 2;
	step = 1.0 / segments;
	i = 0;
	while (i < segments)
	{
		t = i * step;
		curr = catmull_rom_point(spline, t);
		next = catmull_rom_point(spline, t + step);
		next.color = interpolate_color(spline.p1.color, spline.p2.color, t
				+ step);
		draw_line(g, curr, next);
		i++;
	}
}
