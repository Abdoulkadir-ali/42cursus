/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   culling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:21:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

/**
 * @brief Test whether a screen position lies inside the extended viewport.
 * @param pos Screen-space position to test.
 * @param g Graphics context providing window size and frustum margin.
 * @return `1` when the point is considered on screen, otherwise `0`.
 */
int	is_on_screen(t_vec2 pos, t_graphics *g)
{
	int	margin;

	margin = g->camera->frustum_margin;
	return ((int)pos.x >= -margin && (int)pos.x < (int)g->window->width + margin
		&& (int)pos.y >= -margin && (int)pos.y < (int)g->window->height
		+ margin);
}

/**
 * @brief Decide whether a projected line segment is worth drawing.
 * @param p1 First projected point.
 * @param p2 Second projected point.
 * @param g Graphics context providing the viewport.
 * @return `1` when the line should be drawn, otherwise `0`.
 */
int	should_draw_line(t_point p1, t_point p2, t_graphics *g)
{
	if (p1.pos.x <= DRAW_LIMIT || p1.pos.y <= DRAW_LIMIT
		|| p1.pos.z <= DRAW_LIMIT || p2.pos.x <= DRAW_LIMIT
		|| p2.pos.y <= DRAW_LIMIT || p2.pos.z <= DRAW_LIMIT)
		return (0);
	if (!is_on_screen((t_vec2){p1.pos.x, p1.pos.y}, g)
		&& !is_on_screen((t_vec2){p2.pos.x, p2.pos.y}, g))
	{
		if ((p1.pos.x < 0 && p2.pos.x < 0) || (p1.pos.x > g->window->width
				&& p2.pos.x > g->window->width) || (p1.pos.y < 0
				&& p2.pos.y < 0) || (p1.pos.y > g->window->height
				&& p2.pos.y > g->window->height))
			return (0);
	}
	return (1);
}

/**
 * @brief Check whether a projected triangle is back-facing in screen space.
 * @param p1 First projected triangle vertex.
 * @param p2 Second projected triangle vertex.
 * @param p3 Third projected triangle vertex.
 * @return `1` when the triangle is considered back-facing, otherwise `0`.
 */
int	is_backface(t_point p1, t_point p2, t_point p3)
{
	t_vec2d	v1;
	t_vec2d	v2;
	double	cross_z;

	v1 = create_vec2d(p2.pos.x - p1.pos.x, p2.pos.y - p1.pos.y);
	v2 = create_vec2d(p3.pos.x - p1.pos.x, p3.pos.y - p1.pos.y);
	cross_z = v1.x * v2.y - v1.y * v2.x;
	return (cross_z <= 0);
}
