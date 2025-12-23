/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:15:42 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 21:17:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	raycast_draw_pixel_no_z(t_graphics *g, t_bresenham_ctx *ctx,
		t_bresenham_params *p)
{
	t_vec3	rgb;
	t_vec3	shift_vals;
	t_vec3	color;

	rgb = (t_vec3){ctx->fp_r >> FP_SHIFT, ctx->fp_g >> FP_SHIFT,
		ctx->fp_b >> FP_SHIFT};
	shift_vals = (t_vec3){g->camera->color_shift.x, g->camera->color_shift.y,
		g->camera->color_shift.z};
	color = shift_color(rgb, shift_vals);
	draw_pixel_fast_no_z((t_pixel_draw_params){.pixel_addr = p->pixel_addr,
		.color = rgb_to_int(color)});
}

void	raycast_draw_pixel_with_z(t_graphics *g, t_bresenham_ctx *ctx,
		t_bresenham_params *p)
{
	t_vec3	rgb;
	t_vec3	shift_vals;
	t_vec3	color;

	rgb = (t_vec3){ctx->fp_r >> FP_SHIFT, ctx->fp_g >> FP_SHIFT,
		ctx->fp_b >> FP_SHIFT};
	shift_vals = (t_vec3){g->camera->color_shift.x, g->camera->color_shift.y,
		g->camera->color_shift.z};
	color = shift_color(create_color(rgb.x, rgb.y, rgb.z), shift_vals);
	draw_pixel_fast(g, (t_pixel_draw_params){.pixel_addr = p->pixel_addr,
		.z_addr = p->z_addr, .zr = (float)p->zr, .color = rgb_to_int(color)});
}

int	raycast_process_pixel(t_graphics *g, t_bresenham_ctx *ctx,
		t_bresenham_params *p, int use_z)
{
	if (ctx->current.x >= (int)p->min_x && ctx->current.x < (int)p->max_x)
	{
		if (ctx->current.y < g->horizon_buffer[ctx->current.x])
		{
			g->horizon_buffer[ctx->current.x] = ctx->current.y;
			if (use_z)
				raycast_draw_pixel_with_z(g, ctx, p);
			else
				raycast_draw_pixel_no_z(g, ctx, p);
		}
	}
	return (0);
}
