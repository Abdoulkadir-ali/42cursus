/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 00:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/23 20:58:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	bresenham_fast(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx		ctx;
	t_pixel_draw_params	params;
	t_vec3				color;

	(void)g;
	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		color = create_color(ctx.fp_r >> FP_SHIFT, ctx.fp_g >> FP_SHIFT,
				ctx.fp_b >> FP_SHIFT);
		params = (t_pixel_draw_params){.pixel_addr = p->pixel_addr,
			.color = rgb_to_int(color)};
		draw_pixel_fast_no_z(params);
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}

void	bresenham_z(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx		ctx;
	t_pixel_draw_params	params;
	t_vec3				color;

	(void)g;
	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		color = create_color(ctx.fp_r >> FP_SHIFT, ctx.fp_g >> FP_SHIFT,
				ctx.fp_b >> FP_SHIFT);
		params = (t_pixel_draw_params){.pixel_addr = p->pixel_addr,
			.z_addr = p->z_addr, .zr = (float)p->zr,
			.color = rgb_to_int(color)};
		draw_pixel_fast(g, params);
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}

void	bresenham_shift_no_z(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx		ctx;
	t_pixel_draw_params	params;
	t_vec3				color;

	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		color = create_color(ctx.fp_r >> FP_SHIFT, ctx.fp_g >> FP_SHIFT,
				ctx.fp_b >> FP_SHIFT);
		color = shift_color(color, g->camera->color_shift);
		params = (t_pixel_draw_params){.pixel_addr = p->pixel_addr,
			.color = rgb_to_int(color)};
		draw_pixel_fast_no_z(params);
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}

void	bresenham_shift_z(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx		ctx;
	t_pixel_draw_params	params;
	t_vec3				color;

	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		color = create_color(ctx.fp_r >> FP_SHIFT, ctx.fp_g >> FP_SHIFT,
				ctx.fp_b >> FP_SHIFT);
		color = shift_color(color, g->camera->color_shift);
		params = (t_pixel_draw_params){.pixel_addr = p->pixel_addr,
			.z_addr = p->z_addr, .zr = (float)p->zr,
			.color = rgb_to_int(color)};
		draw_pixel_fast(g, params);
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}
