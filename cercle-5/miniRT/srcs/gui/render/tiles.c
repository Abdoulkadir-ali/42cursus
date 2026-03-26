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

static void	render_tile(t_render_ctx *ctx, int id)
{
	t_tile	v;

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

void	*render_tile_worker(void *arg)
{
	t_render_thread_arg	*wa;
	t_render_ctx		*ctx;
	int					id;
	int					idx;

	wa = (t_render_thread_arg *)arg;
	idx = wa->idx;
	while (1)
	{
		sem_wait(&wa->gui->pool.start[idx]);
		if (wa->gui->pool.shutdown)
			break ;
		ctx = wa->gui->pool.ctx[idx];
		while (1)
		{
			id = __sync_fetch_and_add(&ctx->next_tile_id, 1);
			if (id >= ctx->total_tiles)
				break ;
			render_tile(ctx, id);
		}
		PROF_FLUSH();
		sem_post(&wa->gui->pool.done[idx]);
	}
	return (NULL);
}

void	render_tiles(t_render_ctx *ctx)
{
	int	num_cores;
	int	i;

	num_cores = ctx->gui->render.num_cores;
	if (num_cores < 1 || !ctx->gui->pool.ready)
		return ;
	i = 0;
	while (i < num_cores)
	{
		ctx->gui->pool.ctx[i] = ctx;
		sem_post(&ctx->gui->pool.start[i]);
		i++;
	}
	i = 0;
	while (i < num_cores)
	{
		sem_wait(&ctx->gui->pool.done[i]);
		i++;
	}
}
