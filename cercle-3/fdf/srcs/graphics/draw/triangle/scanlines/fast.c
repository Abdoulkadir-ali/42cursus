/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:06:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Draw one scanline without z-buffer tests or color shifting.
 * @param ctx Mutable scanline draw context.
 */
void	draw_scanline_fast_flat(t_scanline_draw_ctx *ctx)
{
	while (ctx->x <= ctx->end_x)
	{
		*(unsigned int *)ctx->pixel_addr = process_flat_color(ctx);
		vec3_add(&ctx->color_ctx.rgb1, ctx->color_ctx.drgb);
		ctx->pixel_addr += 4;
		ctx->x++;
	}
}

/**
 * @brief Draw one scanline without z-buffer tests but with color shifting.
 * @param g Graphics state providing the active color shift.
 * @param ctx Mutable scanline draw context.
 */
void	draw_scanline_fast_shifted(t_graphics *g, t_scanline_draw_ctx *ctx)
{
	while (ctx->x <= ctx->end_x)
	{
		*(unsigned int *)ctx->pixel_addr = process_shifted_color(ctx,
				g->camera->color_shift);
		vec3_add(&ctx->color_ctx.rgb1, ctx->color_ctx.drgb);
		ctx->pixel_addr += 4;
		ctx->x++;
	}
}
