/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:11:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 13:04:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <immintrin.h>
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

/* Standard Scalar Projection Loop (No AVX) */
void	cache_projections(t_graphics *g)
{
	int		x;
	int		y;
	size_t	idx;

	if (!g || !g->map || !g->camera)
		return ;
	update_rotation_matrix(g->camera);
	
	/* Reallocate cache if needed (Cache remains 1D for performance) */
	if (cached_map != g->map || cached_w != g->map->width || cached_h != g->map->height)
	{
		cleanup_cache();
		cached = malloc(sizeof(t_point) * g->map->width * g->map->height);
		if (!cached) return ;
		cached_w = g->map->width;
		cached_h = g->map->height;
		cached_map = g->map;
	}

	y = 0;
	while (y < g->map->height)
	{
		x = 0;
		while (x < g->map->width)
		{
			idx = y * g->map->width + x;
			
			/* Read from 2D Map -> Write to 1D Cache */
			/* Check for BAD_VALUE to preserve safety */
			if (g->map->points.pos[y][x].z <= BAD_VALUE)
			{
				cached[idx].pos.x = BAD_VALUE;
			}
			else
			{
				cached[idx] = project_point(g->map->points.pos[y][x],
						g->map->points.color[y][x], g->camera, g->map->z_divisor);
			}
			x++;
		}
		y++;
	}
}

t_point	get_cached_proj(t_graphics *g, int x, int y)
{
    /* ... (keep existing bounds checks) ... */
	if (cached && cached_map == g->map && x >= 0 && y >= 0 && x < cached_w && y < cached_h)
	{
		return (cached[y * cached_w + x]); /* Cache is 1D */
	}
    /* Fallback: Read from 2D Map */
	return (project_point(g->map->points.pos[y][x], 
			g->map->points.color[y][x],
			g->camera, g->map->z_divisor));
}
