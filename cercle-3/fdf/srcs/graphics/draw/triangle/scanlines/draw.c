/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 00:33:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/*
** Specialized loop for Z-buffering (Slower due to Z check)
*/
static void	draw_scanline_z(t_graphics *g, t_scanline_draw_ctx *ctx)
{
	int	color;

	while (ctx->x <= ctx->end_x)
	{
		if (g->render_config.use_depth_culling && ctx->z_ptr
			&& ctx->z < *ctx->z_ptr)
		{
			*ctx->z_ptr = ctx->z;
			color = create_color(ctx->color_ctx.rgb1.x >> 16,
					ctx->color_ctx.rgb1.y >> 16, ctx->color_ctx.rgb1.z >> 16);
			if (g->camera->color_shift.x | g->camera->color_shift.y
				| g->camera->color_shift.z)
				color = shift_color(color, g->camera->color_shift.x,
						g->camera->color_shift.z, g->camera->color_shift.y);
			*(unsigned int *)ctx->pixel_addr = color;
		}
		ctx->color_ctx.rgb1.x += ctx->color_ctx.drgb.x;
		ctx->color_ctx.rgb1.y += ctx->color_ctx.drgb.y;
		ctx->color_ctx.rgb1.z += ctx->color_ctx.drgb.z;
		ctx->z += ctx->dz;
		ctx->pixel_addr += 4;
		if (ctx->z_ptr)
			ctx->z_ptr++;
		ctx->x++;
	}
}

/*
** Specialized loop for NO Z-buffering (Faster)
*/
static void	draw_scanline_fast(t_graphics *g, t_scanline_draw_ctx *ctx)
{
	int	color;

	while (ctx->x <= ctx->end_x)
	{
		color = create_color(ctx->color_ctx.rgb1.x >> 16,
				ctx->color_ctx.rgb1.y >> 16, ctx->color_ctx.rgb1.z >> 16);
		if (g->camera->color_shift.x | g->camera->color_shift.y
			| g->camera->color_shift.z)
			color = shift_color(color, g->camera->color_shift.x,
					g->camera->color_shift.z, g->camera->color_shift.y);
		*(unsigned int *)ctx->pixel_addr = color;
		ctx->color_ctx.rgb1.x += ctx->color_ctx.drgb.x;
		ctx->color_ctx.rgb1.y += ctx->color_ctx.drgb.y;
		ctx->color_ctx.rgb1.z += ctx->color_ctx.drgb.z;
		ctx->z += ctx->dz;
		ctx->pixel_addr += 4;
		ctx->x++;
	}
}

void	draw_scanline_loop(t_graphics *g, t_scanline_draw_ctx *ctx)
{
	if (g->render_config.use_depth_culling)
		draw_scanline_z(g, ctx);
	else
		draw_scanline_fast(g, ctx);
}

void	draw_scanline_pixel(t_graphics *g, t_scanline_draw_ctx *ctx)
{
	(void)g;
	(void)ctx;
}

void	draw_horizontal_scanline_z(t_graphics *g, t_scanline_data data)
{
	int						len;
	t_scanline_color_ctx	color_ctx;
	float					dz;
	t_scanline_draw_ctx		draw_ctx;

	if (data.x1 > data.x2)
		swap_scanline_data(&data);
	if (data.y < 0 || data.y >= (int)g->window->height)
		return ;
	len = data.x2 - data.x1;
	if (len == 0)
		return ;
	init_scanline_colors(data, len, &color_ctx);
	dz = (data.z2 - data.z1) / (float)len;
	init_scanline_pointers(g, data, &draw_ctx.pixel_addr, &draw_ctx.z_ptr);
	draw_ctx.x = data.x1;
	draw_ctx.end_x = data.x2;
	draw_ctx.color_ctx = color_ctx;
	draw_ctx.z = data.z1;
	draw_ctx.dz = dz;
	clip_scanline_left(&draw_ctx, dz);
	draw_ctx.end_x = clip_scanline_right(draw_ctx.end_x, g->window->width);
	draw_scanline_loop(g, &draw_ctx);
}
