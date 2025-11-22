/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 13:20:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* Define a threshold that is definitely off-screen but safer than BAD_VALUE */
#define DRAW_LIMIT -1000000.0

int	is_point_visible(t_vec3d p, t_graphics *g)
{
	/* Don't render BAD_VALUE points */
	if (p.z <= DRAW_LIMIT)
		return (0);
		
	t_point	projected;
	int		threshold;
	int		z;

	projected = project_point(p, 0, g->camera, g->map->z_divisor);
	threshold = g->camera->dampening_threshold;
	if (threshold == 0)
		return (1);
	z = projected.pos.z;
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
	/* Check for BAD_VALUE points - don't draw lines to/from invalid points */
	if (p1.pos.x <= DRAW_LIMIT || p1.pos.y <= DRAW_LIMIT || p1.pos.z <= DRAW_LIMIT ||
		p2.pos.x <= DRAW_LIMIT || p2.pos.y <= DRAW_LIMIT || p2.pos.z <= DRAW_LIMIT)
		return (0);
		
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