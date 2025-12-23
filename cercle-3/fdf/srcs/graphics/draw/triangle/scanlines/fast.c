/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 22:12:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

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
