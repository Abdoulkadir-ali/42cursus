/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:15:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:31:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Draw one raycast-managed pixel without z-buffer updates.
 * @param g Graphics state providing the color shift.
 * @param ctx Bresenham state holding the current interpolated color.
 * @param p Bresenham parameter block containing the target pixel pointer.
 */
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

/**
 * @brief Draw one raycast-managed pixel with z-buffer updates.
 * @param g Graphics state providing color shift and depth settings.
 * @param ctx Bresenham state holding the current interpolated color.
 * @param p Bresenham parameter block containing pixel and z-buffer pointers.
 */
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

/**
 * @brief Update the horizon buffer and draw one visible raycast pixel.
 * @param g Graphics state owning the horizon buffer.
 * @param ctx Bresenham state holding the current screen position.
 * @param p Bresenham parameter block containing strip bounds and pointers.
 * @param use_z Non-zero to use z-buffer drawing, zero otherwise.
 * @return Always `0` for call-site convenience.
 */
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
