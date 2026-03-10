/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:06:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Dispatch a scanline to the z-buffer-aware inner loop.
 * @param g Graphics state providing color-shift settings.
 * @param ctx Mutable scanline draw context.
 */
static void	draw_scanline_z(t_graphics *g, t_scanline_draw_ctx *ctx)
{
	if (g->camera->color_shift.x | g->camera->color_shift.y
		| g->camera->color_shift.z)
		draw_scanline_z_shifted(g, ctx);
	else
		draw_scanline_z_flat(g, ctx);
}

/**
 * @brief Dispatch a scanline to the fast non-z-buffer inner loop.
 * @param g Graphics state providing color-shift settings.
 * @param ctx Mutable scanline draw context.
 */
static void	draw_scanline_fast(t_graphics *g, t_scanline_draw_ctx *ctx)
{
	if (g->camera->color_shift.x | g->camera->color_shift.y
		| g->camera->color_shift.z)
		draw_scanline_fast_shifted(g, ctx);
	else
		draw_scanline_fast_flat(ctx);
}

/**
 * @brief Draw one prepared scanline using the active depth mode.
 * @param g Graphics state providing render configuration.
 * @param ctx Mutable scanline draw context.
 */
void	draw_scanline_loop(t_graphics *g, t_scanline_draw_ctx *ctx)
{
	if (g->render_config.use_depth_culling)
		draw_scanline_z(g, ctx);
	else
		draw_scanline_fast(g, ctx);
}
