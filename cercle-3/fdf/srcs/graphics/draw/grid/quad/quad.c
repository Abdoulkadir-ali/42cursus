/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:58:16 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:31:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Draw one sampled grid cell as two triangles.
 * @param g Graphics state providing the cached projections.
 * @param x Map-space x index for the cell origin.
 * @param y Map-space y index for the cell origin.
 * @param step Grid sampling step.
 */
void	draw_triangle_quad(t_graphics *g, int x, int y, int step)
{
	t_triangle_quad_ctx	ctx;

	if (x + step >= (int)g->map->width || y + step >= (int)g->map->height)
		return ;
	ctx.idx = y * g->map->width + x;
	ctx.next_row_idx = (y + step) * g->map->width + x;
	ctx.p1 = g->cache.points[ctx.idx];
	ctx.p2 = g->cache.points[ctx.idx + step];
	ctx.p3 = g->cache.points[ctx.next_row_idx];
	ctx.p4 = g->cache.points[ctx.next_row_idx + step];
	if (!is_on_screen((t_vec2){ctx.p1.pos.x, ctx.p1.pos.y}, g)
		&& !is_on_screen((t_vec2){ctx.p2.pos.x, ctx.p2.pos.y}, g)
		&& !is_on_screen((t_vec2){ctx.p3.pos.x, ctx.p3.pos.y}, g)
		&& !is_on_screen((t_vec2){ctx.p4.pos.x, ctx.p4.pos.y}, g))
		return ;
	draw_quad_triangles(g, (t_quad_triangle){ctx.p1, ctx.p2, ctx.p3, ctx.p4});
}

/**
 * @brief Initialize per-row traversal state for one grid row.
 * @param ctx Row traversal context to populate.
 * @param g Graphics state providing map dimensions.
 * @param y Row index being processed.
 * @param lod_value Active LOD step value.
 */
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

/**
 * @brief Process one sampled point within a grid row.
 * @param g Graphics state providing render mode and cached points.
 * @param ctx Mutable row traversal context.
 * @param y Row index being processed.
 */
void	process_grid_row_point(t_graphics *g, t_grid_row_ctx *ctx, int y)
{
	ctx->idx = ctx->row_base + ctx->x;
	if (g->cache.points == NULL || ctx->idx >= ctx->total_points)
		return ;
	if (g->render_config.render_mode == RENDER_TRIANGLES
		|| (g->render_config.render_mode == RENDER_LINES
			&& g->render_config.filled))
	{
		draw_triangle_quad(g, ctx->x, y, ctx->step_int);
		ctx->x += ctx->step_int;
		return ;
	}
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

/**
 * @brief Draw one sampled grid row using the active render mode.
 * @param g Graphics state providing map and cache data.
 * @param y Row index to draw.
 * @param lod_value Active LOD step value.
 */
void	draw_grid_row(t_graphics *g, int y, float lod_value)
{
	t_grid_row_ctx	ctx;

	init_grid_row_ctx(&ctx, g, y, lod_value);
	while (ctx.x < g->map->width)
	{
		process_grid_row_point(g, &ctx, y);
	}
}
