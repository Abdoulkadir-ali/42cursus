/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:58:16 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 12:09:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	init_cache(t_graphics *g)
{
	int		needs_update;
	size_t	size;

	needs_update = g->cache.map != g->map || g->cache.width != g->map->width
		|| g->cache.height != g->map->height;
	if (needs_update)
	{
		cleanup_cache(g);
		size = sizeof(t_point) * g->map->width * g->map->height;
		g->cache.points = malloc(size);
		if (!g->cache.points)
			return ;
		g->cache.width = g->map->width;
		g->cache.height = g->map->height;
		g->cache.map = g->map;
	}
}

void	fill_cache(t_graphics *g)
{
	t_fill_cache_ctx	ctx;

	ctx.y = 0;
	while (ctx.y < g->map->height)
	{
		ctx.x = 0;
		while (ctx.x < g->map->width)
		{
			ctx.idx = ctx.y * g->map->width + ctx.x;
			if (g->map->points.pos[ctx.idx].z <= BAD_VALUE + 1.0)
				g->cache.points[ctx.idx].pos = create_vec3d(BAD_VALUE,
						BAD_VALUE, BAD_VALUE);
			else
			{
				ctx.projected = project_point(g->map->points.pos[ctx.idx],
						g->map->points.color[ctx.idx], g->camera,
						g->map->z_divisor);
				g->cache.points[ctx.idx] = ctx.projected;
			}
			ctx.x++;
		}
		ctx.y++;
	}
}
