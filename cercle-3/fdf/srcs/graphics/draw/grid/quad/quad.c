/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:58:16 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 16:04:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	init_grid_row_ctx(t_grid_row_ctx *ctx, t_graphics *g, int y,
		float lod_value)
{
	ctx->x = 0;
	ctx->step_int = (int)lod_value;
	if (ctx->step_int < 1)
		ctx->step_int = 1;
	ctx->total_points = g->map->width * g->map->height;
	ctx->row_base = y * g->map->width;
}

void	process_grid_row_point(t_graphics *g, t_grid_row_ctx *ctx, int y)
{
	ctx->idx = ctx->row_base + ctx->x;
	if (g->cache.points == NULL || ctx->idx >= ctx->total_points)
		return ;
	ctx->next_x = ctx->x + ctx->step_int;
	if (ctx->next_x < g->map->width)
	{
		draw_segment(g, (t_draw_line_params){{ctx->x, y},
			g->cache.points[ctx->idx], ctx->step_int}, 1);
	}
	if (y + ctx->step_int < (int)g->map->height)
	{
		draw_segment(g, (t_draw_line_params){{ctx->x, y},
			g->cache.points[ctx->idx], ctx->step_int}, 0);
	}
	ctx->x += ctx->step_int;
}

void	draw_grid_row(t_graphics *g, int y, float lod_value)
{
	t_grid_row_ctx	ctx;

	init_grid_row_ctx(&ctx, g, y, lod_value);
	while (ctx.x < g->map->width)
	{
		process_grid_row_point(g, &ctx, y);
	}
}
