/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:06:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Draw one scanline with z-buffer tests and no color shifting.
 * @param g Graphics state providing the depth-culling setting.
 * @param ctx Mutable scanline draw context.
 */
void	draw_scanline_z_flat(t_graphics *g, t_scanline_draw_ctx *ctx)
{
	while (ctx->x <= ctx->end_x)
	{
		if (g->render_config.use_depth_culling && *(ctx->z_ptr) > ctx->z)
		{
			*(ctx->z_ptr) = ctx->z;
			*(unsigned int *)ctx->pixel_addr = process_flat_color(ctx);
		}
		vec3_add(&ctx->color_ctx.rgb1, ctx->color_ctx.drgb);
		ctx->z += ctx->dz;
		ctx->pixel_addr += 4;
		ctx->z_ptr++;
		ctx->x++;
	}
}

/**
 * @brief Draw one scanline with z-buffer tests and color shifting.
 * @param g Graphics state providing depth and color-shift settings.
 * @param ctx Mutable scanline draw context.
 */
void	draw_scanline_z_shifted(t_graphics *g, t_scanline_draw_ctx *ctx)
{
	while (ctx->x <= ctx->end_x)
	{
		if (g->render_config.use_depth_culling && *(ctx->z_ptr) > ctx->z)
		{
			*(ctx->z_ptr) = ctx->z;
			*(unsigned int *)ctx->pixel_addr = process_shifted_color(ctx,
					g->camera->color_shift);
		}
		vec3_add(&ctx->color_ctx.rgb1, ctx->color_ctx.drgb);
		ctx->z += ctx->dz;
		ctx->pixel_addr += 4;
		ctx->z_ptr++;
		ctx->x++;
	}
}
