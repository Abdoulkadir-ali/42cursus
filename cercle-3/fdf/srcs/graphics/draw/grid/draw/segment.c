/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:46:31 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 13:11:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void compute_next_coords(t_segment_ctx *ctx, t_draw_line_params params,
		int is_horizontal)
{
	if (is_horizontal)
	{
		ctx->next_x = params.x + params.step;
		ctx->next_y = params.y;
	}
	else
	{
		ctx->next_x = params.x;
		ctx->next_y = params.y + params.step;
	}
}

static void compute_prev_next(t_segment_ctx *ctx, t_graphics *g,
		t_draw_line_params params, int is_horizontal)
{
	if (is_horizontal)
	{
		ctx->prev_coord = params.x - params.step;
		ctx->next_coord = ctx->next_x + params.step;
		ctx->max_coord = g->map->width;
	}
	else
	{
		ctx->prev_coord = params.y - params.step;
		ctx->next_coord = ctx->next_y + params.step;
		ctx->max_coord = g->map->height;
	}
}

static void compute_p0_p3(t_segment_ctx *ctx, t_graphics *g,
		t_draw_line_params params, t_point p2)
{
	if (ctx->prev_coord >= 0)
	{
		if (ctx->prev_coord == params.x - params.step)
			ctx->p0 = get_cached_proj(g, ctx->prev_coord, params.y);
		else
			ctx->p0 = get_cached_proj(g, params.x, ctx->prev_coord);
	}
	else
		ctx->p0 = params.p1;
	if (ctx->next_coord < ctx->max_coord)
	{
		if (ctx->next_coord == ctx->next_x + params.step)
			ctx->p3 = get_cached_proj(g, ctx->next_coord, params.y);
		else
			ctx->p3 = get_cached_proj(g, params.x, ctx->next_coord);
	}
	else
		ctx->p3 = p2;
}

void    draw_segment(t_graphics *g, t_draw_line_params params, int is_horizontal)
{
	t_segment_ctx    ctx;
	t_point          p2;

	compute_next_coords(&ctx, params, is_horizontal);
	if (ctx.next_x >= g->map->width || ctx.next_y >= g->map->height)
		return ;
	p2 = get_cached_proj(g, ctx.next_x, ctx.next_y);
	if (!should_draw_line(params.p1, p2, g))
		return ;
	if (g->render_config.render_mode == RENDER_SPLINES)
	{
		compute_prev_next(&ctx, g, params, is_horizontal);
		compute_p0_p3(&ctx, g, params, p2);
		draw_spline_segment(g, (t_spline){ctx.p0, params.p1, p2, ctx.p3},
			g->camera->spline_segments);
	}
	else if (g->render_config.render_mode == RENDER_LINES)
		draw_line(g, params.p1, p2);
}
