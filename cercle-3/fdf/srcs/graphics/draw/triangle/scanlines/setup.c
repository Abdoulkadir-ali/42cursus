/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 21:45:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	init_scanline_ctx(t_graphics *g, t_scanline_data data,
		t_scanline_ctx *ctx)
{
	ctx->len = data.x2 - data.x1;
	init_scanline_colors(data, ctx->len, &ctx->color_ctx);
	ctx->dz = (data.z2 - data.z1) / (float)ctx->len;
	init_scanline_pointers(g, data, &ctx->draw_ctx.pixel_addr,
		&ctx->draw_ctx.z_ptr);
	ctx->draw_ctx.x = data.x1;
	ctx->draw_ctx.end_x = data.x2;
	ctx->draw_ctx.color_ctx = ctx->color_ctx;
	ctx->draw_ctx.z = data.z1;
	ctx->draw_ctx.dz = ctx->dz;
}

void	draw_horizontal_scanline_z(t_graphics *g, t_scanline_data data)
{
	t_scanline_ctx	ctx;

	if (data.x1 > data.x2)
		swap_scanline_data(&data);
	if (data.y < 0 || data.y >= (int)g->window->height)
		return ;
	ctx.len = data.x2 - data.x1;
	if (ctx.len == 0)
		return ;
	init_scanline_ctx(g, data, &ctx);
	clip_scanline_left(&ctx.draw_ctx, ctx.dz);
	ctx.draw_ctx.end_x = clip_scanline_right(ctx.draw_ctx.end_x,
			g->window->width);
	draw_scanline_loop(g, &ctx.draw_ctx);
}
