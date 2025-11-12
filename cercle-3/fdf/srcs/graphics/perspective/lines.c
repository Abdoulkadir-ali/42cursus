/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 21:18:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	is_point_visible(t_point p, t_graphics *g)
{
	int	threshold;
	int	z;

	threshold = g->camera->dampening_threshold;
	if (threshold == 0)
		return (1);
	z = p.pos.z;
	if (threshold < 0)
		return (z >= -threshold);
	else
		return (z <= threshold);
}

int	is_visible(int x, int y, t_graphics *g)
{
	(void)x;
	(void)y;
	return (x >= 0 && x < g->window->width && y >= 0
		&& y < g->window->height);
}

int	is_on_screen(int x, int y, t_graphics *g)
{
	int	margin;

	margin = g->camera->frustum_margin;
	return (x >= -margin && x < g->window->width + margin && y >= -margin
		&& y < g->window->height + margin);
}

int	should_draw_line(t_point p1, t_point p2, t_graphics *g)
{
	if (!is_on_screen(p1.pos.x, p1.pos.y, g) && !is_on_screen(p2.pos.x, p2.pos.y,
			g))
	{
		if ((p1.pos.x < 0 && p2.pos.x < 0) || (p1.pos.x > g->window->width
				&& p2.pos.x > g->window->width) || (p1.pos.y < 0
				&& p2.pos.y < 0) || (p1.pos.y > g->window->height
				&& p2.pos.y > g->window->height))
			return (0);
	}
	return (1);
}