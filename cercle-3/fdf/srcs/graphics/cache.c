/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@local>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 21:30:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/21 21:30:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <stdlib.h>

/*
 * Simple module-local cache keyed by the t_map pointer. This avoids changing
 * the existing graphics struct in the header; it stores a flattened array
 * of t_point (projected positions) and resizes when the map pointer or
 * dimensions change.
 */

static t_point	*cached = NULL;
static int	cached_w = 0;
static int	cached_h = 0;
static t_map	*cached_map = NULL;

void	free_cache(void)
{
	if (cached)
	{
		free(cached);
		cached = NULL;
	}
	cached_w = 0;
	cached_h = 0;
	cached_map = NULL;
}

/* Public cleanup wrapper so other modules can free the cache on exit. */
void	cleanup_cache(void)
{
	free_cache();
}

void	cache_projections(t_graphics *g)
{
	int		w;
	int		h;
	int		x;
	int		y;
	t_point	*p;

	if (!g || !g->map || !g->camera)
		return ;
	w = g->map->width;
	h = g->map->height;
	/* If cached map changed or dimensions changed, reallocate */
	if (cached_map != g->map || cached_w != w || cached_h != h)
	{
		free_cache();
		cached = malloc(sizeof(t_point) * (size_t)w * (size_t)h);
		if (!cached)
			return ;
		cached_w = w;
		cached_h = h;
		cached_map = g->map;
	}

	p = cached;
	x = 0;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			/* project the 3D point once and store it */
			*p = project_point(g->map->points.pos[y][x],
					g->map->points.color[y][x], g->camera, g->map->z_divisor);
			++p;
			++x;
		}
		++y;
	}
}

/* Returns a copy of the cached projected point; if cache not available,
   falls back to calling project_point directly. */
	t_point	get_cached_proj(t_graphics *g, int x, int y)
{
	size_t idx;
	if (!g || !g->map)
		return ((t_point){.pos = {0,0,0}, .color = 0});
	if (cached && cached_map == g->map && x >= 0 && y >= 0 && x < cached_w && y < cached_h)
	{
		idx = (size_t)y * (size_t)cached_w + (size_t)x;
		return (cached[idx]);
	}
	/* fallback */
	return (project_point(g->map->points.pos[y][x], g->map->points.color[y][x],
		g->camera, g->map->z_divisor));
}
