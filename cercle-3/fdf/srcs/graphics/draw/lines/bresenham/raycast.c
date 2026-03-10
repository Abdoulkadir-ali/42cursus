/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 00:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/03/10 03:06:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Draw a horizon-aware line without z-buffer updates.
 * @param g Graphics state providing the horizon buffer.
 * @param p Prepared Bresenham parameter block.
 */
void	bresenham_raycast_fast(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx		ctx;
	t_vec3				rgb;
	t_pixel_draw_params	params;

	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		if (ctx.current.x >= (int)p->min_x && ctx.current.x < (int)p->max_x)
		{
			if (ctx.current.y < g->horizon_buffer[ctx.current.x])
			{
				g->horizon_buffer[ctx.current.x] = ctx.current.y;
				rgb = (t_vec3){ctx.fp_r >> FP_SHIFT, ctx.fp_g >> FP_SHIFT,
					ctx.fp_b >> FP_SHIFT};
				params.pixel_addr = p->pixel_addr;
				params.color = rgb_to_int(rgb);
				draw_pixel_fast_no_z(params);
			}
		}
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}

/**
 * @brief Draw a horizon-aware line with z-buffer updates.
 * @param g Graphics state providing the horizon and z buffers.
 * @param p Prepared Bresenham parameter block.
 */
void	bresenham_raycast_z(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx	ctx;
	t_vec3			rgb;

	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		if (ctx.current.x >= (int)p->min_x && ctx.current.x < (int)p->max_x)
		{
			if (ctx.current.y < g->horizon_buffer[ctx.current.x])
			{
				g->horizon_buffer[ctx.current.x] = ctx.current.y;
				rgb = (t_vec3){ctx.fp_r >> FP_SHIFT, ctx.fp_g >> FP_SHIFT,
					ctx.fp_b >> FP_SHIFT};
				draw_pixel_fast(g,
					(t_pixel_draw_params){.pixel_addr = p->pixel_addr,
					.z_addr = p->z_addr, .zr = (float)p->zr,
					.color = rgb_to_int(rgb)});
			}
		}
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}

/**
 * @brief Draw a horizon-aware color-shifted line without z-buffer updates.
 * @param g Graphics state providing horizon and color-shift settings.
 * @param p Prepared Bresenham parameter block.
 */
void	bresenham_raycast_shift_no_z(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx	ctx;

	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		raycast_process_pixel(g, &ctx, p, 0);
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}

/**
 * @brief Draw a horizon-aware color-shifted line with z-buffer updates.
 * @param g Graphics state providing horizon, depth, and color-shift settings.
 * @param p Prepared Bresenham parameter block.
 */
void	bresenham_raycast_shift_z(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx	ctx;

	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		raycast_process_pixel(g, &ctx, p, 1);
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}
