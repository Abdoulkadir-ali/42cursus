/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:11:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 14:57:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <immintrin.h>
#include <stdlib.h>

void	cleanup_cache(t_graphics *g)
{
	if (g->cache.points)
	{
		free(g->cache.points);
		g->cache.points = NULL;
	}
	g->cache.width = 0;
	g->cache.height = 0;
	g->cache.map = NULL;
}

void	cache_projections(t_graphics *g)
{
	if (!g || !g->map || !g->camera)
		return ;
	update_rotation_matrix(g->camera);
	init_cache(g);
	if (g->cache.points)
		fill_cache(g);
}

t_point	get_fallback_proj(t_graphics *g, int x, int y)
{
	size_t	idx;
	t_point	bad_point;

	idx = y * g->map->width + x;
	if (g->map->points.pos[idx].z <= BAD_VALUE + 1.0)
	{
		bad_point.pos.x = BAD_VALUE;
		bad_point.pos.y = BAD_VALUE;
		bad_point.pos.z = BAD_VALUE;
		bad_point.color = 0;
		return (bad_point);
	}
	return (project_point(g->map->points.pos[idx], g->map->points.color[idx],
			g->camera, g->map->z_divisor));
}

t_point	get_cached_proj(t_graphics *g, int x, int y)
{
	int	valid;

	valid = x >= 0 && y >= 0 && x < g->cache.width && y < g->cache.height;
	if (g->cache.points && g->cache.map == g->map && valid)
		return (g->cache.points[y * g->cache.width + x]);
	return (get_fallback_proj(g, x, y));
}
