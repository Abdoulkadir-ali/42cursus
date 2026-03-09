/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fallback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 04:19:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 04:22:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static t_point	create_bad_point(void)
{
	t_point	bad_point;

	bad_point.pos.x = BAD_VALUE;
	bad_point.pos.y = BAD_VALUE;
	bad_point.pos.z = BAD_VALUE;
	bad_point.color = create_color(0, 0, 0);
	return (bad_point);
}

static t_point	get_valid_proj(t_graphics *g, int x, int y)
{
	size_t	idx;
	t_vec3d	p3d;
	t_point	p_in;

	idx = y * g->map->width + x;
	p3d = g->map->points.pos[idx];
	if (g->camera->use_z_divisor && g->map->z_divisor != 0)
		p3d.z /= (double)g->map->z_divisor;
	p_in.pos = p3d;
	p_in.color = g->map->points.color[idx];
	return (apply_transform(p_in, g->camera));
}

static t_point	get_fallback_proj(t_graphics *g, int x, int y)
{
	size_t	idx;

	if (!g || !g->map || !g->map->points.pos)
		return (create_bad_point());
	idx = y * g->map->width + x;
	if (g->map->points.pos[idx].z <= BAD_VALUE + 1.0)
		return (create_bad_point());
	return (get_valid_proj(g, x, y));
}

t_point	get_cached_proj(t_graphics *g, int x, int y)
{
	if (g->cache.points && g->cache.map == g->map && x >= 0 && y >= 0
		&& (size_t)x < g->cache.width && (size_t)y < g->cache.height)
		return (g->cache.points[y * g->cache.width + x]);
	return (get_fallback_proj(g, x, y));
}
