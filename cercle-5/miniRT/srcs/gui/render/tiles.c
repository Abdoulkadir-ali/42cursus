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

static void	render_tile(t_render *ctx, int id)
{
	t_tile	v;

	v.tile_idx.x = (id % ctx->tiles_x) * TILE_SIZE;
	v.tile_idx.y = (id / ctx->tiles_x) * TILE_SIZE;
	v.pos.y = v.tile_idx.y;
	v.row_ptr = ctx->gui->win.addr
		+ (v.pos.y * ctx->gui->win.line_len)
		+ (v.tile_idx.x * (ctx->gui->win.bpp / 8));
	v.bpp_step = (ctx->gui->win.bpp / 8) * ctx->step;
	v.row_step = ctx->gui->win.line_len * ctx->step;
	while (v.pos.y < v.tile_idx.y + TILE_SIZE && v.pos.y < ctx->gui->win.size.y)
	{
		v.pos.x = v.tile_idx.x;
		v.pixel_ptr = v.row_ptr;
		while (v.pos.x < v.tile_idx.x + TILE_SIZE && v.pos.x < ctx->gui->win.size.x)
		{
			process_pixel(ctx, vec2i(v.pos.x, v.pos.y), v.pixel_ptr);
			v.pos.x += ctx->step;
			v.pixel_ptr += v.bpp_step;
		}
		v.pos.y += ctx->step;
		v.row_ptr += v.row_step;
	}
}

static void	run_worker_frame(t_render_thread_arg *wa, int idx)
{
	t_render	*ctx;
	int			id;

	ctx = wa->gui->pool.ctx[idx];
	pthread_rwlock_rdlock(&wa->gui->scene_lock);
	while (1)
	{
		id = __sync_fetch_and_add(&ctx->next_tile_id, 1);
		if (id >= ctx->total_tiles)
			break ;
		render_tile(ctx, id);
	}
	pthread_rwlock_unlock(&wa->gui->scene_lock);
	PROF_FLUSH();
	sem_post(&wa->gui->pool.done[idx]);
}

void	*render_tile_worker(void *arg)
{
	t_render_thread_arg	*wa;
	int				idx;

	wa = (t_render_thread_arg *)arg;
	idx = wa->idx;
	while (1)
	{
		sem_wait(&wa->gui->pool.start[idx]);
		if (wa->gui->pool.shutdown)
			break ;
		run_worker_frame(wa, idx);
	}
	return (NULL);
}

void	render_tiles(t_render *ctx)
{
	int	num_cores;
	int	i;

	num_cores = ctx->gui->render.num_cores;
	if (num_cores < 1 || !ctx->gui->pool.ready)
		return ;
	i = 0;
	pthread_rwlock_wrlock(&ctx->gui->scene_lock);
	while (i < num_cores)
	{
		ctx->gui->pool.ctx[i] = ctx;
		i++;
	}
	pthread_rwlock_unlock(&ctx->gui->scene_lock);
	i = 0;
	while (i < num_cores)
	{
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
