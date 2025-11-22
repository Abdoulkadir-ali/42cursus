/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:11:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 04:33:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <stdlib.h>

static t_point	*cached = NULL;
static int		cached_w = 0;
static int		cached_h = 0;
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

void	cleanup_cache(void)
{
	free_cache();
}

void	cache_projections(t_graphics *g)
{
	int		w;
	int		h;

	if (!g || !g->map || !g->camera)
		return ;
	update_rotation_matrix(g->camera);
	w = g->map->width;
	h = g->map->height;
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
	size_t total = (size_t)w * (size_t)h;
	size_t i = 0;
	while (i < total)
	{
		cached[i] = project_point(g->map->points.pos[i],
				g->map->points.color[i], g->camera, g->map->z_divisor);
		i++;
	}
}

t_point	get_cached_proj(t_graphics *g, int x, int y)
{
	size_t	idx;

	if (!g || !g->map)
		return ((t_point){.pos = {0, 0, 0}, .color = 0});
	if (cached && cached_map == g->map && x >= 0 && y >= 0 && x < cached_w
		&& y < cached_h)
	{
		idx = (size_t)y * (size_t)cached_w + (size_t)x;
		return (cached[idx]);
	}
	/* fallback */
	return (project_point(g->map->points.pos[y * g->map->width + x], g->map->points.color[y * g->map->width + x],
			g->camera, g->map->z_divisor));
}
