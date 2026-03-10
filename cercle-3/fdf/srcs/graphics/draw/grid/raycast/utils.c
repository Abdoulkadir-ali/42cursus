/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 19:12:41 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:31:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Fetch one cached point when the requested map indices are valid.
 * @param g Graphics state providing the active map and cache.
 * @param x Map-space x index.
 * @param y Map-space y index.
 * @param p Output point storage.
 * @return `1` when a valid point was written, otherwise `0`.
 */
int	get_point(t_graphics *g, int x, int y, t_point *p)
{
	if (x < 0 || x >= (int)g->map->width || y < 0 || y >= (int)g->map->height)
		return (0);
	*p = get_cached_proj(g, x, y);
	if (p->pos.x <= BAD_VALUE)
		return (0);
	return (1);
}

/**
 * @brief Seed the peak-selection context with candidate sample positions.
 * @param ctx Peak-selection context to initialize.
 * @param g Graphics state providing map dimensions.
 */
void	init_peak_indicies(t_get_peak_ctx *ctx, t_graphics *g)
{
	ctx->w = g->map->width;
	ctx->h = g->map->height;
	ctx->max_y = -1000000.0f;
	ctx->peak.x = 0;
	ctx->peak.y = 0;
	ctx->xs[0] = 0;
	ctx->xs[1] = ctx->w / 2;
	ctx->xs[2] = ctx->w - 1;
	ctx->ys[0] = 0;
	ctx->ys[1] = ctx->h / 2;
	ctx->ys[2] = ctx->h - 1;
	ctx->yi = 0;
}

/**
 * @brief Approximate the highest visible map sample among a 3x3 probe set.
 * @param g Graphics state providing cached projections.
 * @return Map indices of the selected peak sample.
 */
t_vec2	get_peak_indices(t_graphics *g)
{
	t_get_peak_ctx	ctx;

	init_peak_indicies(&ctx, g);
	while (ctx.yi < 3)
	{
		ctx.xi = 0;
		while (ctx.xi < 3)
		{
			ctx.p = get_cached_proj(g, ctx.xs[ctx.xi], ctx.ys[ctx.yi]);
			if (ctx.p.pos.y > ctx.max_y)
			{
				ctx.max_y = ctx.p.pos.y;
				ctx.peak.x = ctx.xs[ctx.xi];
				ctx.peak.y = ctx.ys[ctx.yi];
			}
			ctx.xi++;
		}
		ctx.yi++;
	}
	return (ctx.peak);
}

/**
 * @brief Build a surface-draw context for one raycast traversal step.
 * @param g Graphics state providing render data.
 * @param pos Current map-space position.
 * @param dir Neighbor direction for this sweep.
 * @param t Thread payload containing strip bounds.
 * @return Initialized surface-draw context.
 */
t_draw_surface_ctx	init_draw_surface_ctx(t_graphics *g, t_vec2 pos, t_vec2 dir,
		t_thread_data *t)
{
	t_draw_surface_ctx	ctx;

	ctx.g = g;
	ctx.pos = pos;
	ctx.dir = dir;
	ctx.t = t;
	ctx.curr = (t_point){0};
	ctx.h_next = (t_point){0};
	ctx.v_next = (t_point){0};
	ctx.diag = (t_point){0};
	ctx.has_curr = 0;
	ctx.has_h = 0;
	ctx.has_v = 0;
	ctx.has_diag = 0;
	ctx.margin = 50;
	return (ctx);
}
