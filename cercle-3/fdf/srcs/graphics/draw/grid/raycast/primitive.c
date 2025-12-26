/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:27:48 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 15:28:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	draw_horizontal_line(t_draw_surface_ctx *ctx)
{
	t_clipping_bounds	bounds;

	if (ctx->dir.x != 0 && ctx->has_h)
	{
		if (!((ctx->curr.pos.x < ctx->t->min_visible_x
					&& ctx->h_next.pos.x < ctx->t->min_visible_x)
				|| (ctx->curr.pos.x >= ctx->t->max_visible_x
					&& ctx->h_next.pos.x >= ctx->t->max_visible_x)))
		{
			bounds.min_x = ctx->t->min_visible_x;
			bounds.max_x = ctx->t->max_visible_x;
			draw_line_clipped(ctx->g, ctx->curr, ctx->h_next, bounds);
		}
	}
}

static void	draw_vertical_line(t_draw_surface_ctx *ctx)
{
	t_clipping_bounds	bounds;

	if (ctx->dir.y != 0 && ctx->has_v)
	{
		if (!((ctx->curr.pos.x < ctx->t->min_visible_x
					&& ctx->v_next.pos.x < ctx->t->min_visible_x)
				|| (ctx->curr.pos.x >= ctx->t->max_visible_x
					&& ctx->v_next.pos.x >= ctx->t->max_visible_x)))
		{
			bounds.min_x = ctx->t->min_visible_x;
			bounds.max_x = ctx->t->max_visible_x;
			draw_line_clipped(ctx->g, ctx->curr, ctx->v_next, bounds);
		}
	}
}

static void	draw_lines(t_draw_surface_ctx *ctx)
{
	if (ctx->g->render_config.render_mode == RENDER_LINES)
	{
		draw_horizontal_line(ctx);
		draw_vertical_line(ctx);
	}
	else if (ctx->g->render_config.render_mode == RENDER_POINTS)
	{
		img_pixel_put_with_z(ctx->g, ctx->curr);
	}
}

void	draw_surface_primitive(t_draw_surface_ctx *ctx)
{
	ctx->margin = 50;
	ctx->has_curr = get_point(ctx->g, ctx->pos.x, ctx->pos.y, &ctx->curr);
	if (!ctx->has_curr)
		return ;
	ctx->has_h = get_point(ctx->g, ctx->pos.x + ctx->dir.x, ctx->pos.y,
			&ctx->h_next);
	ctx->has_v = get_point(ctx->g, ctx->pos.x, ctx->pos.y + ctx->dir.y,
			&ctx->v_next);
	ctx->has_diag = 0;
	draw_lines(ctx);
}
