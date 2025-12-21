/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:58:16 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 00:33:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	swap_scanline_data(t_scanline_data *data)
{
	float	tmp_z;
	int		tmp_c;

	ft_swap(&data->x1, &data->x2);
	tmp_z = data->z1;
	data->z1 = data->z2;
	data->z2 = tmp_z;
	tmp_c = data->c1;
	data->c1 = data->c2;
	data->c2 = tmp_c;
}

void	init_scanline_colors(t_scanline_data data, int len,
		t_scanline_color_ctx *ctx)
{
	ctx->rgb1.x = get_red(data.c1) * FP_16;
	ctx->rgb1.y = get_green(data.c1) * FP_16;
	ctx->rgb1.z = get_blue(data.c1) * FP_16;
	ctx->rgb2.x = get_red(data.c2) * FP_16;
	ctx->rgb2.y = get_green(data.c2) * FP_16;
	ctx->rgb2.z = get_blue(data.c2) * FP_16;
	ctx->drgb.x = (ctx->rgb2.x - ctx->rgb1.x) / len;
	ctx->drgb.y = (ctx->rgb2.y - ctx->rgb1.y) / len;
	ctx->drgb.z = (ctx->rgb2.z - ctx->rgb1.z) / len;
}

void	init_scanline_pointers(t_graphics *g, t_scanline_data data,
		char **pixel_addr, float **z_ptr)
{
	*pixel_addr = g->window->main_img.img_addr + (data.y
			* g->window->main_img.img_line_len) + (data.x1
			* (g->window->main_img.img_bpp / 8));
	*z_ptr = NULL;
	if (g->window->z_buffer)
		*z_ptr = g->window->z_buffer + (data.y * g->window->width) + data.x1;
}

void	clip_scanline_left(t_scanline_draw_ctx *ctx, float dz)
{
	int	skip;

	if (ctx->x < 0)
	{
		skip = -ctx->x;
		ctx->x = 0;
		ctx->color_ctx.rgb1.x += ctx->color_ctx.drgb.x * skip;
		ctx->color_ctx.rgb1.y += ctx->color_ctx.drgb.y * skip;
		ctx->color_ctx.rgb1.z += ctx->color_ctx.drgb.z * skip;
		ctx->z += dz * skip;
		ctx->pixel_addr += skip * 4;
		if (ctx->z_ptr)
			ctx->z_ptr += skip;
	}
}

int	clip_scanline_right(int end_x, size_t win_w)
{
	if (end_x >= (int)win_w)
		return (win_w - 1);
	return (end_x);
}
