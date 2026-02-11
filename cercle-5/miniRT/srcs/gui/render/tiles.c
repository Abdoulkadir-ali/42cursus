/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 20:30:00 by abdoali          #+#    #+#             */
/*   Updated: 2026/02/11 20:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

struct s_tile_vars
{
	int		id;
	int		tx;
	int		ty;
	int		x;
	int		y;
	int		bpp_step;
	int		row_step;
	char	*row_ptr;
	char	*pixel_ptr;
};

static void	render_tile(t_render_ctx *ctx, int id)
{
	struct s_tile_vars	v;

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
			process_pixel(ctx, v.x, v.y, v.pixel_ptr);
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
	int			id;

	ctx = (t_render_ctx *)arg;
	while (1)
	{
		pthread_mutex_lock(&ctx->mutex);
		if (ctx->next_tile_id >= ctx->total_tiles)
		{
			pthread_mutex_unlock(&ctx->mutex);
			break ;
		}
		id = ctx->next_tile_id++;
		pthread_mutex_unlock(&ctx->mutex);
		render_tile(ctx, id);
	}
	return (NULL);
}

static void	start_threads(pthread_t *threads, t_render_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_create(&threads[i], NULL, render_tile_worker, ctx);
		i++;
	}
}

static void	join_threads(pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	render_tiles(t_render_ctx *ctx)
{
	pthread_t	threads[THREAD_COUNT];

	start_threads(threads, ctx);
	join_threads(threads);
}
