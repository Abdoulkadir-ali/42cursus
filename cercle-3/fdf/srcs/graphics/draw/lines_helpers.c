/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 04:00:34 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 05:05:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	setup_pointers(t_graphics *g, t_ptr_ctx *ctx, int sx, int sy)
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

static void	init_interpolation(t_point start, t_point end, int steps,
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