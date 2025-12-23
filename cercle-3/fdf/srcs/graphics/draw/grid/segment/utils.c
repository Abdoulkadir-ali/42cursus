/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:40:11 by abdoali          #+#    #+#             */
/*   Updated: 2025/12/23 19:40:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	compute_next_coords(t_segment_ctx *ctx, t_draw_line_params params,
		int is_horizontal)
{
	if (is_horizontal)
	{
		ctx->next_x = params.pos.x + params.step;
		ctx->next_y = params.pos.y;
	}
	else
	{
		ctx->next_x = params.pos.x;
		ctx->next_y = params.pos.y + params.step;
	}
}

t_tessellation_ctx	init_tessellation_ctx(t_segment_ctx *ctx, t_graphics *g,
		t_draw_line_params params)
{
	t_tessellation_ctx	t_ctx;

	t_ctx.steps = (int)(1.0 / g->render_config.lod_value);
	t_ctx.total_base = (long)g->map->width * g->map->height;
	t_ctx.max_steps = 300000 / (2 * t_ctx.total_base);
	if (t_ctx.max_steps < 2)
		t_ctx.max_steps = 2;
	if (t_ctx.steps > t_ctx.max_steps)
		t_ctx.steps = t_ctx.max_steps;
	if (t_ctx.steps > 16)
		t_ctx.steps = 16;
	t_ctx.v1 = g->map->points.pos[(int)params.pos.y * g->map->width
		+ (int)params.pos.x];
	t_ctx.v2 = g->map->points.pos[ctx->next_y * g->map->width + ctx->next_x];
	t_ctx.c1 = g->map->points.color[(int)params.pos.y * g->map->width
		+ (int)params.pos.x];
	t_ctx.c2 = g->map->points.color[ctx->next_y * g->map->width + ctx->next_x];
	t_ctx.prev = params.p1;
	t_ctx.k = 1;
	return (t_ctx);
}
