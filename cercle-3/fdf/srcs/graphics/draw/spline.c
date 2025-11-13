/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spline.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 13:32:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

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
