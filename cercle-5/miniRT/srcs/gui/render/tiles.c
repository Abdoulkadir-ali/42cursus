/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 06:02:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 06:02:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "profiler.h"
#include <semaphore.h>

#define RENDER_POOL_MAX 128

typedef struct s_render_pool
{
	pthread_t		threads[RENDER_POOL_MAX];
	sem_t			start[RENDER_POOL_MAX];
	sem_t			done[RENDER_POOL_MAX];
	t_render_ctx	*ctx[RENDER_POOL_MAX];
	int				n;
	bool			shutdown;
}	t_render_pool;

static t_render_pool	g_pool;
static bool				g_pool_ready = false;

static void	render_tile(t_render_ctx *ctx, int id)
{
	t_tile_vars	v;

	v.tx = (id % ctx->tiles_x) * TILE_SIZE;
	v.ty = (id / ctx->tiles_x) * TILE_SIZE;
	v.y = v.ty;
	v.row_ptr = ctx->gui->win.addr
		+ (v.y * ctx->gui->win.line_len)
		+ (v.tx * (ctx->gui->win.bpp / 8));
	v.bpp_step = (ctx->gui->win.bpp / 8) * ctx->step;
	v.row_step = ctx->gui->win.line_len * ctx->step;
	while (v.y < v.ty + TILE_SIZE && v.y < ctx->gui->win.height)
	{
		v.x = v.tx;
		v.pixel_ptr = v.row_ptr;
		while (v.x < v.tx + TILE_SIZE && v.x < ctx->gui->win.width)
		{
			process_pixel(ctx, vec2i(v.x, v.y), v.pixel_ptr);
			v.x += ctx->step;
			v.pixel_ptr += v.bpp_step;
		}
		v.y += ctx->step;
		v.row_ptr += v.row_step;
	}
}

static void	*render_tile_worker(void *arg)
{
	int				idx;
	t_render_ctx	*ctx;
	int				id;

	idx = (int)(intptr_t)arg;
	while (1)
	{
		sem_wait(&g_pool.start[idx]);
		if (g_pool.shutdown)
			break ;
		ctx = g_pool.ctx[idx];
		while (1)
		{
			id = __sync_fetch_and_add(&ctx->next_tile_id, 1);
			if (id >= ctx->total_tiles)
				break ;
			render_tile(ctx, id);
		}
		PROF_FLUSH();
		sem_post(&g_pool.done[idx]);
	}
	return (NULL);
}

static void	init_render_pool(int n)
{
	int	i;

	g_pool.n = n;
	g_pool.shutdown = false;
	i = 0;
	while (i < n)
	{
		sem_init(&g_pool.start[i], 0, 0);
		sem_init(&g_pool.done[i], 0, 0);
		g_pool.ctx[i] = NULL;
		pthread_create(&g_pool.threads[i], NULL, render_tile_worker,
			(void *)(intptr_t)i);
		i++;
	}
	g_pool_ready = true;
}

void	render_tiles(t_render_ctx *ctx)
{
	int	num_cores;
	int	i;

	num_cores = ctx->gui->render.num_cores;
	if (num_cores < 1)
		return ;
	if (!g_pool_ready)
		init_render_pool(num_cores);
	i = 0;
	while (i < num_cores)
	{
		g_pool.ctx[i] = ctx;
		sem_post(&g_pool.start[i]);
		i++;
	}
	i = 0;
	while (i < num_cores)
	{
		sem_wait(&g_pool.done[i]);
		i++;
	}
}
