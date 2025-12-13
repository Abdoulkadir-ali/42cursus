/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:13:09 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 12:15:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	draw_pixel_fast(t_graphics *g, t_pixel_draw_params p)
{
	if (!g->render_config.use_depth_culling || !p.z_addr || p.zr < *p.z_addr)
	{
		if (g->render_config.use_depth_culling && p.z_addr)
			*p.z_addr = p.zr;
		*(unsigned int *)p.pixel_addr = p.color;
	}
}

static void	draw_pixel_fast_no_z(t_pixel_draw_params p)
{
	*(unsigned int *)p.pixel_addr = p.color;
}


int	init_draw_line_ctx(t_graphics *g, t_point start, t_point end,
		t_draw_line_ctx *dlc)
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
	setup_pointers(g, &dlc->ctx, dlc->sign.x, dlc->sign.y);
	if (dlc->start_pos.x < 0 || dlc->start_pos.x >= dlc->ctx.width
		|| dlc->start_pos.y < 0 || dlc->start_pos.y >= dlc->ctx.height)
		return (0);
	dlc->pixel_addr = g->window->main_img.img_addr + (dlc->start_pos.y
			* dlc->ctx.line_len) + (dlc->start_pos.x * dlc->ctx.bpp);
	dlc->z_addr = NULL;
	if (g->window->z_buffer)
		dlc->z_addr = g->window->z_buffer + (dlc->start_pos.y * dlc->ctx.width)
			+ dlc->start_pos.x;
	if (dlc->delta.x > dlc->delta.y)
		dlc->steps = dlc->delta.x;
	else
		dlc->steps = dlc->delta.y;
	init_interpolation(start, end, dlc->steps, &dlc->interp);
	return (1);
}

void	draw_line(t_graphics *g, t_point start, t_point end)
{
	t_draw_line_ctx dlc;

	if (!init_draw_line_ctx(g, start, end, &dlc))
		return ;

	dlc.p.start = dlc.start_pos;
	dlc.p.end = dlc.end_pos;
	dlc.p.delta = dlc.delta;
	dlc.p.sign = dlc.sign;
	dlc.p.ctx = dlc.ctx;
	dlc.p.pixel_addr = dlc.pixel_addr;
	dlc.p.z_addr = dlc.z_addr;
	dlc.p.zr = dlc.interp.zr;
	dlc.p.z_step_val = dlc.interp.z_step_val;
	dlc.p.r = dlc.interp.r;
	dlc.p.green = dlc.interp.green;
	dlc.p.b = dlc.interp.b;
	dlc.p.dr = dlc.interp.dr;
	dlc.p.dg = dlc.interp.dg;
	dlc.p.db = dlc.interp.db;
	if (g->render_config.use_depth_culling)
	{
		if (g->camera->color_shift.x || g->camera->color_shift.y
			|| g->camera->color_shift.z)
			bresenham_fixed_shifted(g, dlc.p);
		else
			bresenham_fixed(g, dlc.p);
	}
	else
	{
		if (g->camera->color_shift.x || g->camera->color_shift.y
			|| g->camera->color_shift.z)
			bresenham_fixed_no_z_shifted(g, dlc.p);
		else
			bresenham_fixed_no_z(dlc.p);
	}
}