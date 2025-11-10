/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spline.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 20:22:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "spline.h"

double	catmull_rom_interpolate(double p0, double p1, double p2,
		double p3, double t)
{
	double	t2;
	double	t3;
	double	result;

	t2 = t * t;
	t3 = t2 * t;
	result = 0.5 * (
			(2.0 * p1) +
			(-p0 + p2) * t +
			(2.0 * p0 - 5.0 * p1 + 4.0 * p2 - p3) * t2 +
			(-p0 + 3.0 * p1 - 3.0 * p2 + p3) * t3
		);
	return (result);
}


static t_point	catmull_rom_point(t_point p0, t_point p1,
		t_point p2, t_point p3, double t)
{
	t_point	result;

	result.pos.x = catmull_rom_interpolate(p0.pos.x, p1.pos.x,
			p2.pos.x, p3.pos.x, t);
	result.pos.y = catmull_rom_interpolate(p0.pos.y, p1.pos.y,
			p2.pos.y, p3.pos.y, t);
	result.pos.z = 0;
	result.color = p1.color;
	return (result);
}

static int	lerp_color(int c1, int c2, double t)
{
	int	r1;
	int	g1;
	int	b1;
	int	r2;
	int	g2;
	int	b2;
	int	r;
	int	g;
	int	b;

	r1 = (c1 >> 16) & 0xFF;
	g1 = (c1 >> 8) & 0xFF;
	b1 = c1 & 0xFF;
	r2 = (c2 >> 16) & 0xFF;
	g2 = (c2 >> 8) & 0xFF;
	b2 = c2 & 0xFF;
	r = (int)(r1 + (r2 - r1) * t);
	g = (int)(g1 + (g2 - g1) * t);
	b = (int)(b1 + (b2 - b1) * t);
	return ((r << 16) | (g << 8) | b);
}

void	draw_spline_segment(t_data *data, t_point p0, t_point p1,
		t_point p2, t_point p3, int segments)
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
		curr = catmull_rom_point(p0, p1, p2, p3, t);
		next = catmull_rom_point(p0, p1, p2, p3, t + step);
		// Interpolate color along the curve
		next.color = lerp_color(p1.color, p2.color, t + step);
		draw_line(data, curr, next);
		i++;
	}
}

t_point	lerp_point(t_point p1, t_point p2, double t)
{
	t_point	result;

	result.pos.x = p1.pos.x + (p2.pos.x - p1.pos.x) * t;
	result.pos.y = p1.pos.y + (p2.pos.y - p1.pos.y) * t;
	result.pos.z = 0;
	result.color = lerp_color(p1.color, p2.color, t);
	return (result);
}
