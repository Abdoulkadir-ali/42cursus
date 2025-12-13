/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:58:16 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 12:36:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	setup_edge(t_edge *e, t_point top, t_point bot)
{
	int		height;
	double	inv_h;

	height = (int)bot.pos.y - (int)top.pos.y;
	if (height <= 0)
		return ;
	inv_h = 1.0 / height;
	e->x = top.pos.x;
	e->z = top.pos.z;
	e->r = get_red(top.color);
	e->g = get_green(top.color);
	e->b = get_blue(top.color);
	e->dx = (bot.pos.x - top.pos.x) * inv_h;
	e->dz = (bot.pos.z - top.pos.z) * inv_h;
	e->dr = (get_red(bot.color) - e->r) * inv_h;
	e->dg = (get_green(bot.color) - e->g) * inv_h;
	e->db = (get_blue(bot.color) - e->b) * inv_h;
}

static void	step_edge(t_edge *e)
{
	e->x += e->dx;
	e->z += e->dz;
	e->r += e->dr;
	e->g += e->dg;
	e->b += e->db;
}

static void	swap_points(t_point *a, t_point *b)
{
	t_point	t;

	t = *a;
	*a = *b;
	*b = t;
}
