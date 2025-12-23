/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:00:00 by abdoali          #+#    #+#             */
/*   Updated: 2025/12/23 20:00:00 by abdoali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	draw_upper_half(t_thread_raycast_ctx *ctx)
{
	t_draw_surface_ctx	prim_ctx;

	ctx->current.y = ctx->peak.y;
	while (ctx->current.y >= 0)
	{
		ctx->current.x = ctx->peak.x;
		while (ctx->current.x >= 0)
		{
			prim_ctx = init_draw_surface_ctx(ctx->g, ctx->current,
					(t_vec2){-ctx->step, -ctx->step}, ctx->t);
			draw_surface_primitive(&prim_ctx);
			ctx->current.x -= ctx->step;
		}
		ctx->current.x = ctx->peak.x + ctx->step;
		while (ctx->current.x < ctx->w)
		{
			prim_ctx = init_draw_surface_ctx(ctx->g, ctx->current,
					(t_vec2){ctx->step, -ctx->step}, ctx->t);
			draw_surface_primitive(&prim_ctx);
			ctx->current.x += ctx->step;
		}
		ctx->current.y -= ctx->step;
	}
}

static void	draw_lower_half(t_thread_raycast_ctx *ctx)
{
	t_draw_surface_ctx	prim_ctx;

	ctx->current.y = ctx->peak.y + ctx->step;
	while (ctx->current.y < ctx->h)
	{
		ctx->current.x = ctx->peak.x;
		while (ctx->current.x >= 0)
		{
			prim_ctx = init_draw_surface_ctx(ctx->g, ctx->current,
					(t_vec2){-ctx->step, ctx->step}, ctx->t);
			draw_surface_primitive(&prim_ctx);
			ctx->current.x -= ctx->step;
		}
		ctx->current.x = ctx->peak.x + ctx->step;
		while (ctx->current.x < ctx->w)
		{
			prim_ctx = init_draw_surface_ctx(ctx->g, ctx->current,
					(t_vec2){ctx->step, ctx->step}, ctx->t);
			draw_surface_primitive(&prim_ctx);
			ctx->current.x += ctx->step;
		}
		ctx->current.y += ctx->step;
	}
}

void	*thread_raycast_routine(void *data)
{
	t_thread_raycast_ctx	ctx;

	ctx.t = (t_thread_data *)data;
	ctx.g = ctx.t->g;
	ctx.w = ctx.g->map->width;
	ctx.h = ctx.g->map->height;
	ctx.peak = get_peak_indices(ctx.g);
	ctx.step = (int)ctx.g->render_config.lod_value;
	if (ctx.step < 1)
		ctx.step = 1;
	draw_upper_half(&ctx);
	draw_lower_half(&ctx);
	return (NULL);
}
