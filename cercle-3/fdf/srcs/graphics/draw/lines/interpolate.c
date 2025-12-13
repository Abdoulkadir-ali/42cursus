/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 04:00:34 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 12:14:57 by abdoali          ###   ########.fr       */
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

