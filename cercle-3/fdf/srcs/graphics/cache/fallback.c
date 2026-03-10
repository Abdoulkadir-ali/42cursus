/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fallback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 04:19:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:31:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Create a sentinel point representing invalid projected data.
 * @return Point initialized with bad coordinates and a black color.
 */
static t_point	create_bad_point(void)
{
	t_point	bad_point;

	bad_point.pos.x = BAD_VALUE;
	bad_point.pos.y = BAD_VALUE;
	bad_point.pos.z = BAD_VALUE;
	bad_point.color = create_color(0, 0, 0);
	return (bad_point);
}

/**
 * @brief Compute one projected point directly from the live map data.
 * @param g Graphics state providing map and camera data.
 * @param x Map-space x index.
 * @param y Map-space y index.
 * @return Newly transformed screen-space point.
 */
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

/**
 * @brief Return a fallback point, rejecting invalid source map entries.
 * @param g Graphics state providing map and camera data.
 * @param x Map-space x index.
 * @param y Map-space y index.
 * @return Cached-style point or a bad sentinel when unavailable.
 */
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

/**
 * @brief Return a projected point from the cache or compute a fallback.
 * @param g Graphics state providing cache, map, and camera data.
 * @param x Map-space x index.
 * @param y Map-space y index.
 * @return Cached point when valid, otherwise a fallback projection.
 */
t_point	get_cached_proj(t_graphics *g, int x, int y)
{
	if (g->cache.points && g->cache.map == g->map && x >= 0 && y >= 0
		&& (size_t)x < g->cache.width && (size_t)y < g->cache.height)
		return (g->cache.points[y * g->cache.width + x]);
	return (get_fallback_proj(g, x, y));
}
