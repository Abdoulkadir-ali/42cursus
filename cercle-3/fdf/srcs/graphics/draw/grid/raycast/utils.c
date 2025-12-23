/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:00:00 by abdoali          #+#    #+#             */
/*   Updated: 2025/12/23 20:00:00 by abdoali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	get_point(t_graphics *g, int x, int y, t_point *p)
{
	if (x < 0 || x >= (int)g->map->width || y < 0 || y >= (int)g->map->height)
		return (0);
	*p = get_cached_proj(g, x, y);
	if (p->pos.x <= BAD_VALUE)
		return (0);
	return (1);
}

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
