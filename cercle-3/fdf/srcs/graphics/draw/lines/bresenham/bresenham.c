/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 00:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/21 00:33:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* Standard Variants (No Checks) */

static void	bresenham_fast(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx	ctx;
	unsigned int	color;

	(void)g;
	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		color = create_color(ctx.fp_r >> FP_SHIFT, ctx.fp_g >> FP_SHIFT,
				ctx.fp_b >> FP_SHIFT);
		draw_pixel_fast_no_z((t_pixel_draw_params){.pixel_addr = p->pixel_addr,
			.color = color});
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}

static void	bresenham_z(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx	ctx;
	unsigned int	color;

	(void)g;
	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		color = create_color(ctx.fp_r >> FP_SHIFT, ctx.fp_g >> FP_SHIFT,
				ctx.fp_b >> FP_SHIFT);
		draw_pixel_fast(g, (t_pixel_draw_params){.pixel_addr = p->pixel_addr,
			.z_addr = p->z_addr, .zr = (float)p->zr, .color = color});
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}

static void	bresenham_shift_no_z(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx	ctx;
	unsigned int	color;

	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		color = create_color(ctx.fp_r >> FP_SHIFT, ctx.fp_g >> FP_SHIFT,
				ctx.fp_b >> FP_SHIFT);
		color = shift_color(color, g->camera->color_shift.x,
				g->camera->color_shift.y, g->camera->color_shift.z);
		draw_pixel_fast_no_z((t_pixel_draw_params){.pixel_addr = p->pixel_addr,
			.color = color});
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}

static void	bresenham_shift_z(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx	ctx;
	unsigned int	color;

	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		color = create_color(ctx.fp_r >> FP_SHIFT, ctx.fp_g >> FP_SHIFT,
				ctx.fp_b >> FP_SHIFT);
		color = shift_color(color, g->camera->color_shift.x,
				g->camera->color_shift.y, g->camera->color_shift.z);
		draw_pixel_fast(g, (t_pixel_draw_params){.pixel_addr = p->pixel_addr,
			.z_addr = p->z_addr, .zr = (float)p->zr, .color = color});
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}

/* Raycast Variants (With Horizon Check) */

static void	bresenham_raycast_fast(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx	ctx;
	unsigned int	color;

	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		if (ctx.current.x >= (int)p->min_x && ctx.current.x < (int)p->max_x)
		{
			if (ctx.current.y < g->horizon_buffer[ctx.current.x])
			{
				g->horizon_buffer[ctx.current.x] = ctx.current.y;
				color = create_color(ctx.fp_r >> FP_SHIFT, ctx.fp_g >> FP_SHIFT,
						ctx.fp_b >> FP_SHIFT);
				draw_pixel_fast_no_z((t_pixel_draw_params){.pixel_addr = p->pixel_addr,
					.color = color});
			}
		}
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}

static void	bresenham_raycast_z(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx	ctx;
	int				color;

	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		if (ctx.current.x >= (int)p->min_x && ctx.current.x < (int)p->max_x)
		{
			if (ctx.current.y < g->horizon_buffer[ctx.current.x])
			{
				g->horizon_buffer[ctx.current.x] = ctx.current.y;
				color = create_color(ctx.fp_r >> FP_SHIFT, ctx.fp_g >> FP_SHIFT,
						ctx.fp_b >> FP_SHIFT);
				draw_pixel_fast(g, (t_pixel_draw_params){.pixel_addr = p->pixel_addr,
					.z_addr = p->z_addr, .zr = (float)p->zr, .color = color});
			}
		}
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}

static void	bresenham_raycast_shift_no_z(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx	ctx;
	int				color;

	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		if (ctx.current.x >= (int)p->min_x && ctx.current.x < (int)p->max_x)
		{
			if (ctx.current.y < g->horizon_buffer[ctx.current.x])
			{
				g->horizon_buffer[ctx.current.x] = ctx.current.y;
				color = create_color(ctx.fp_r >> FP_SHIFT, ctx.fp_g >> FP_SHIFT,
						ctx.fp_b >> FP_SHIFT);
				color = shift_color(color, g->camera->color_shift.x,
						g->camera->color_shift.y, g->camera->color_shift.z);
				draw_pixel_fast_no_z((t_pixel_draw_params){.pixel_addr = p->pixel_addr,
					.color = color});
			}
		}
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}

static void	bresenham_raycast_shift_z(t_graphics *g, t_bresenham_params *p)
{
	t_bresenham_ctx	ctx;
	int				color;

	init_bresenham_ctx(&ctx, p);
	while (1)
	{
		if (ctx.current.x >= (int)p->min_x && ctx.current.x < (int)p->max_x)
		{
			if (ctx.current.y < g->horizon_buffer[ctx.current.x])
			{
				g->horizon_buffer[ctx.current.x] = ctx.current.y;
				color = create_color(ctx.fp_r >> FP_SHIFT, ctx.fp_g >> FP_SHIFT,
						ctx.fp_b >> FP_SHIFT);
				color = shift_color(color, g->camera->color_shift.x,
						g->camera->color_shift.y, g->camera->color_shift.z);
				draw_pixel_fast(g, (t_pixel_draw_params){.pixel_addr = p->pixel_addr,
					.z_addr = p->z_addr, .zr = (float)p->zr, .color = color});
			}
		}
		if (ctx.current.x == p->end.x && ctx.current.y == p->end.y)
			break ;
		if (bresenham_iter(&ctx, p))
			break ;
		update_bresenham_colors(&ctx, p);
	}
}

void	bresenham_raycast(t_graphics *g, t_bresenham_params *p, int flags)
{
	if (flags & B_COLOR_SHIFT)
	{
		if (flags & B_USE_Z)
			bresenham_raycast_shift_z(g, p);
		else
			bresenham_raycast_shift_no_z(g, p);
	}
	else
	{
		if (flags & B_USE_Z)
			bresenham_raycast_z(g, p);
		else
			bresenham_raycast_fast(g, p);
	}
}

void	bresenham(t_graphics *g, t_bresenham_params *p, int flags)
{
	if (flags & B_COLOR_SHIFT)
	{
		if (flags & B_USE_Z)
			bresenham_shift_z(g, p);
		else
			bresenham_shift_no_z(g, p);
	}
	else
	{
		if (flags & B_USE_Z)
			bresenham_z(g, p);
		else
			bresenham_fast(g, p);
	}
}
