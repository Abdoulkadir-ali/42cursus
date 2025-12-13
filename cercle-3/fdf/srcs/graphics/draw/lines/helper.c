/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:27:15 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 15:06:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_pixel_fast(t_graphics *g, t_pixel_draw_params p)
{
	if (!g->render_config.use_depth_culling || !p.z_addr || p.zr < *p.z_addr)
	{
		if (g->render_config.use_depth_culling && p.z_addr)
			*p.z_addr = p.zr;
		*(unsigned int *)p.pixel_addr = p.color;
	}
}

void	draw_pixel_fast_no_z(t_pixel_draw_params p)
{
	*(unsigned int *)p.pixel_addr = p.color;
}

void	fill_bresenham_params(t_draw_line_ctx *dlc)
{
	dlc->p.start = dlc->start_pos;
	dlc->p.end = dlc->end_pos;
	dlc->p.delta = dlc->delta;
	dlc->p.sign = dlc->sign;
	dlc->p.ctx = dlc->ctx;
	dlc->p.pixel_addr = dlc->pixel_addr;
	dlc->p.z_addr = dlc->z_addr;
	dlc->p.zr = dlc->interp.zr;
	dlc->p.z_step_val = dlc->interp.z_step_val;
	dlc->p.r = dlc->interp.r;
	dlc->p.green = dlc->interp.green;
	dlc->p.b = dlc->interp.b;
	dlc->p.dr = dlc->interp.dr;
	dlc->p.dg = dlc->interp.dg;
	dlc->p.db = dlc->interp.db;
}

void	setup_pointers(t_graphics *g, t_ptr_ctx *ctx, int sx, int sy)
{
	ctx->bpp = g->window->main_img.img_bpp / 8;
	ctx->line_len = g->window->main_img.img_line_len;
	ctx->width = g->window->width;
	ctx->height = g->window->height;
	ctx->step_x = sx * ctx->bpp;
	ctx->step_y = sy * ctx->line_len;
	ctx->z_step_x = sx;
	ctx->z_step_y = sy * ctx->width;
}

void	init_interpolation(t_point start, t_point end, int steps,
		t_interp_data *data)
{
	t_vec3	start_rgb;
	t_vec3	end_rgb;

	data->zr = start.pos.z;
	if (steps > 0)
		data->z_step_val = (end.pos.z - start.pos.z) / steps;
	else
		data->z_step_val = 0;
	start_rgb = get_vec3(start.color);
	end_rgb = get_vec3(end.color);
	data->r = start_rgb.x;
	data->green = start_rgb.y;
	data->b = start_rgb.z;
	if (steps > 0)
	{
		data->dr = (end_rgb.x - data->r) / steps;
		data->dg = (end_rgb.y - data->green) / steps;
		data->db = (end_rgb.z - data->b) / steps;
	}
	else
	{
		data->dr = 0;
		data->dg = 0;
		data->db = 0;
	}
}
