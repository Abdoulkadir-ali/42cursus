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
	t_render_ctx	*ctx;
	int				id;

	ctx = (t_render_ctx *)arg;
	while (1)
	{
		id = __sync_fetch_and_add(&ctx->next_tile_id, 1);
		if (id >= ctx->total_tiles)
			break ;
		render_tile(ctx, id);
	}
	PROF_FLUSH();
	return (NULL);
}

static void	start_threads(pthread_t *threads, t_render_ctx *ctx, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_create(&threads[i], NULL, render_tile_worker, ctx);
		i++;
	}
}

static void	join_threads(pthread_t *threads, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	render_tiles(t_render_ctx *ctx)
{
	pthread_t		*threads;
	struct timeval	start;
	struct timeval	end;
	int				num_cores;

	num_cores = ctx->gui->render.num_cores;
	threads = ctx->gui->render.threads;
	if (!threads || num_cores < 1)
		return ;
	gettimeofday(&start, NULL);
	start_threads(threads, ctx, num_cores);
	join_threads(threads, num_cores);
	gettimeofday(&end, NULL);
}
