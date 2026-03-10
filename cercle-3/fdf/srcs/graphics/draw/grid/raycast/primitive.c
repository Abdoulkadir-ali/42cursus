/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:27:48 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:07:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Draw the horizontal neighbor line for one surface primitive.
 * @param ctx Surface-draw context containing the current point and strip bounds.
 */
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

/**
 * @brief Draw the vertical neighbor line for one surface primitive.
 * @param ctx Surface-draw context containing the current point and strip bounds.
 */
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

/**
 * @brief Emit wireframe lines for the current surface primitive when enabled.
 * @param ctx Surface-draw context containing the current cached neighbors.
 */
static void	draw_lines(t_draw_surface_ctx *ctx)
{
	if (ctx->g->render_config.render_mode == RENDER_LINES
		&& !ctx->g->render_config.filled)
	{
		draw_horizontal_line(ctx);
		draw_vertical_line(ctx);
	}
}

/**
 * @brief Emit filled triangles for the current surface primitive when enabled.
 * @param ctx Surface-draw context containing the current cached neighbors.
 */
static void	draw_triangles(t_draw_surface_ctx *ctx)
{
	if (ctx->g->render_config.render_mode == RENDER_TRIANGLES
		|| (ctx->g->render_config.render_mode == RENDER_LINES
			&& ctx->g->render_config.filled))
	{
		if (ctx->has_h && ctx->has_v)
			draw_triangle(ctx->g, ctx->curr, ctx->h_next, ctx->v_next);
		if (ctx->has_h && ctx->has_v && ctx->has_diag)
			draw_triangle(ctx->g, ctx->h_next, ctx->diag, ctx->v_next);
	}
}

/**
 * @brief Draw one raycast traversal primitive from the cached grid.
 * @param ctx Surface-draw context with position, direction, and strip data.
 */
void	draw_surface_primitive(t_draw_surface_ctx *ctx)
{
	ctx->margin = 50;
	ctx->has_curr = get_point(ctx->g, ctx->pos.x, ctx->pos.y, &ctx->curr);
	if (!ctx->has_curr)
		return ;
	check_visibility(ctx);
	ctx->has_h = get_point(ctx->g, ctx->pos.x + ctx->dir.x, ctx->pos.y,
			&ctx->h_next);
	ctx->has_v = get_point(ctx->g, ctx->pos.x, ctx->pos.y + ctx->dir.y,
			&ctx->v_next);
	ctx->has_diag = 0;
	if ((ctx->g->render_config.render_mode == RENDER_TRIANGLES
			|| (ctx->g->render_config.render_mode == RENDER_LINES
				&& ctx->g->render_config.filled)))
		ctx->has_diag = get_point(ctx->g, ctx->pos.x + ctx->dir.x, ctx->pos.y
				+ ctx->dir.y, &ctx->diag);
	draw_lines(ctx);
	draw_triangles(ctx);
}
