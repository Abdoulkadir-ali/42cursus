/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 18:15:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"

static int	realloc_tile_buffers(t_thread_pool *p)
{
	free(p->tiles);
	free(p->jobs);
	p->tiles = (t_tile *)malloc(sizeof(t_tile) * p->n_tiles);
	p->jobs = (t_tile_job *)malloc(sizeof(t_tile_job) * p->n_tiles);
	if (!p->tiles || !p->jobs)
		return (0);
	p->cap_tiles = p->n_tiles;
	return (1);
}

static inline void	set_tile(t_tile *tile, t_vec2i t, int w, int h)
{
	tile->x0 = t.x * TILE_SIZE;
	tile->y0 = t.y * TILE_SIZE;
	tile->x1 = (tile->x0 + TILE_SIZE > w) ? w : tile->x0 + TILE_SIZE;
	tile->y1 = (tile->y0 + TILE_SIZE > h) ? h : tile->y0 + TILE_SIZE;
}

static void	fill_tiles(t_thread_pool *p, t_vec2i n, int w, int h)
{
	t_vec2i	t;
	int		i;

	i = 0;
	t.y = 0;
	while (t.y < n.y)
	{
		t.x = 0;
		while (t.x < n.x)
		{
			set_tile(&p->tiles[i++], (t_vec2i){t.x, t.y}, w, h);
			t.x++;
		}
		t.y++;
	}
}

void	pool_rebuild_tiles(t_thread_pool *p, int w, int h)
{
	t_vec2i	n;

	n.x = (w + TILE_SIZE - 1) / TILE_SIZE;
	n.y = (h + TILE_SIZE - 1) / TILE_SIZE;
	p->n_tiles = n.x * n.y;
	if (p->n_tiles > p->cap_tiles && !realloc_tile_buffers(p))
		return ;
	if (!p->tiles || !p->jobs)
		return ;
	fill_tiles(p, n, w, h);
}
