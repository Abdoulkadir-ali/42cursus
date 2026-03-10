/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:58:16 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:06:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Swap two projected points in place.
 * @param a First point.
 * @param b Second point.
 */
void	swap_points(t_point *a, t_point *b)
{
	t_point	t;

	t = *a;
	*a = *b;
	*b = t;
}

/**
 * @brief Initialize one edge walker between a top and bottom point.
 * @param e Edge structure to populate.
 * @param top Top point of the edge.
 * @param bot Bottom point of the edge.
 */
void	setup_edge(t_edge *e, t_point top, t_point bot)
{
	int		height;
	double	inv_h;

	height = (int)bot.pos.y - (int)top.pos.y;
	if (height <= 0)
		return ;
	inv_h = 1.0 / height;
	e->x = top.pos.x;
	e->z = top.pos.z;
	e->r = top.color.x;
	e->g = top.color.y;
	e->b = top.color.z;
	e->dx = (bot.pos.x - top.pos.x) * inv_h;
	e->dz = (bot.pos.z - top.pos.z) * inv_h;
	e->dr = (bot.color.x - e->r) * inv_h;
	e->dg = (bot.color.y - e->g) * inv_h;
	e->db = (bot.color.z - e->b) * inv_h;
}

/**
 * @brief Advance one edge walker by one scanline.
 * @param e Edge structure to update.
 */
void	step_edge(t_edge *e)
{
	e->x += e->dx;
	e->z += e->dz;
	e->r += e->dr;
	e->g += e->dg;
	e->b += e->db;
}
