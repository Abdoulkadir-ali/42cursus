/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:11:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 13:20:36 by abdoali          ###   ########.fr       */
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
			idx = y * g->map->width + x; // 1D Index Math

			/* Check BAD_VALUE in 1D Array */
			if (g->map->points.pos[idx].z <= BAD_VALUE + 1.0)
			{
				cached[idx].pos.x = BAD_VALUE;
				cached[idx].pos.y = BAD_VALUE;
				cached[idx].pos.z = BAD_VALUE;
			}
			else
			{
				/* Pass 1D data to project_point */
				cached[idx] = project_point(g->map->points.pos[idx],
						g->map->points.color[idx], g->camera, g->map->z_divisor);
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
		return (cached[y * cached_w + x]); // 1D Access
	}
    /* Fallback */
	size_t idx = y * g->map->width + x;
    
    /* Check RAW Z before projecting */
    if (g->map->points.pos[idx].z <= BAD_VALUE + 1.0) /* Tolerance check */
    {
        return ((t_point){.pos = {BAD_VALUE, BAD_VALUE, BAD_VALUE}, .color = 0});
    }
    /* ------------------------ */

	return (project_point(g->map->points.pos[idx], 
			g->map->points.color[idx],
			g->camera, g->map->z_divisor));
}
