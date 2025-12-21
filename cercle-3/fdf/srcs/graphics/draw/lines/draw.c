/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:46:12 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 00:33:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	set_line_positions(t_point start, t_point end, t_draw_line_ctx *dlc)
{
	dlc->start_pos.x = (int)start.pos.x;
	dlc->start_pos.y = (int)start.pos.y;
	dlc->end_pos.x = (int)end.pos.x;
	dlc->end_pos.y = (int)end.pos.y;
	dlc->delta.x = abs(dlc->end_pos.x - dlc->start_pos.x);
	dlc->delta.y = abs(dlc->end_pos.y - dlc->start_pos.y);
	if (dlc->start_pos.x < dlc->end_pos.x)
		dlc->sign.x = 1;
	else
		dlc->sign.x = -1;
	if (dlc->start_pos.y < dlc->end_pos.y)
		dlc->sign.y = 1;
	else
		dlc->sign.y = -1;
}

static int	is_line_visible(t_draw_line_ctx *dlc)
{
	if (dlc->start_pos.x < 0 || dlc->start_pos.x >= (int)dlc->ctx.width
		|| dlc->start_pos.y < 0 || dlc->start_pos.y >= (int)dlc->ctx.height)
		return (0);
	return (1);
}

static void	set_line_pointers(t_graphics *g,
		t_draw_line_ctx *dlc)
{
	dlc->pixel_addr = g->window->main_img.img_addr
		+ (dlc->start_pos.y * dlc->ctx.line_len)
		+ (dlc->start_pos.x * dlc->ctx.bpp);
	dlc->z_addr = NULL;
	if (g->window->z_buffer)
		dlc->z_addr = g->window->z_buffer
			+ (dlc->start_pos.y * dlc->ctx.width)
			+ dlc->start_pos.x;
	if (dlc->delta.x > dlc->delta.y)
		dlc->steps = dlc->delta.x;
	else
		dlc->steps = dlc->delta.y;
}

int	init_draw_line_ctx(t_graphics *g, t_point start, t_point end,
		t_draw_line_ctx *dlc)
{
	set_line_positions(start, end, dlc);
	setup_pointers(g, &dlc->ctx, dlc->sign.x, dlc->sign.y);
	if (!is_line_visible(dlc))
		return (0);
	set_line_pointers(g, dlc);
	init_interpolation(start, end, dlc->steps, &dlc->interp);
	return (1);
}

void	draw_line_clipped(t_graphics *g, t_point start, t_point end,
		size_t min_x, size_t max_x)
{
	t_draw_line_ctx	dlc;

	if (!init_draw_line_ctx(g, start, end, &dlc))
		return ;
	fill_bresenham_params(&dlc);
	dlc.p.min_x = min_x;
	dlc.p.max_x = max_x;
	if (g->render_config.use_horizon_culling)
	{
		if (g->render_config.use_depth_culling)
		{
			if (g->camera->color_shift.x || g->camera->color_shift.y
				|| g->camera->color_shift.z)
				bresenham_raycast(g, &dlc.p, B_USE_Z | B_COLOR_SHIFT);
			else
				bresenham_raycast(g, &dlc.p, B_USE_Z);
		}
		else
		{
			if (g->camera->color_shift.x || g->camera->color_shift.y
				|| g->camera->color_shift.z)
				bresenham_raycast(g, &dlc.p, B_COLOR_SHIFT);
			else
				bresenham_raycast(g, &dlc.p, 0);
		}
	}
	else
	{
		if (g->render_config.use_depth_culling)
		{
			if (g->camera->color_shift.x || g->camera->color_shift.y
				|| g->camera->color_shift.z)
				bresenham(g, &dlc.p, B_USE_Z | B_COLOR_SHIFT);
			else
				bresenham(g, &dlc.p, B_USE_Z);
		}
		else
		{
			if (g->camera->color_shift.x || g->camera->color_shift.y
				|| g->camera->color_shift.z)
				bresenham(g, &dlc.p, B_COLOR_SHIFT);
			else
				bresenham(g, &dlc.p, 0);
		}
	}
}

void	draw_line(t_graphics *g, t_point start, t_point end)
{
	draw_line_clipped(g, start, end, 0, g->window->width);
}
