/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanlines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 05:08:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* Fixed Point Shift */
#define FP_16 65536

void	draw_horizontal_scanline_z(t_graphics *g, t_scanline_data data)
{
	int x;
	int len;

	if (data.x1 > data.x2)
	{
		ft_swap(&data.x1, &data.x2);
		float tmp_z = data.z1;
		data.z1 = data.z2;
		data.z2 = tmp_z;
		int tmp_c = data.c1;
		data.c1 = data.c2;
		data.c2 = tmp_c;
	}
	if (data.y < 0 || data.y >= g->window->height)
		return ;
	len = data.x2 - data.x1;
	if (len == 0)
		return ;
	int r1 = get_red(data.c1) * FP_16;
	int g1 = get_green(data.c1) * FP_16;
	int b1 = get_blue(data.c1) * FP_16;

	int r2 = get_red(data.c2) * FP_16;
	int g2 = get_green(data.c2) * FP_16;
	int b2 = get_blue(data.c2) * FP_16;

	int dr = (r2 - r1) / len;
	int dg = (g2 - g1) / len;
	int db = (b2 - b1) / len;
	float z = data.z1;
	float dz = (data.z2 - data.z1) / (float)len;
	char *pixel_addr = g->window->main_img.img_addr + (data.y
			* g->window->main_img.img_line_len) + (data.x1
			* (g->window->main_img.img_bpp / 8));

	float *z_ptr = NULL;
	if (g->window->z_buffer)
		z_ptr = g->window->z_buffer + (data.y * g->window->width) + data.x1;
	x = data.x1;
	int win_w = g->window->width;
	int end_x = data.x2;
	if (x < 0)
	{
		int skip = -x;
		x = 0;
		r1 += dr * skip;
		g1 += dg * skip;
		b1 += db * skip;
		z += dz * skip;
		pixel_addr += skip * 4;
		if (z_ptr)
			z_ptr += skip;
	}
	if (end_x >= win_w)
		end_x = win_w - 1;

	while (x <= end_x)
	{
		if (!g->render_config.use_depth_culling || !z_ptr || z < *z_ptr)
		{
			if (z_ptr)
				*z_ptr = z;
			int color = create_color(r1 >> 16, g1 >> 16, b1 >> 16);
			if (g->camera->color_shift.x | g->camera->color_shift.y | g->camera->color_shift.z)
				color = shift_color(color, g->camera->color_shift.x,
						g->camera->color_shift.z, g->camera->color_shift.y);

			*(unsigned int *)pixel_addr = color;
		}
		r1 += dr;
		g1 += dg;
		b1 += db;
		z += dz;

		pixel_addr += 4;
		if (z_ptr)
			z_ptr++;
		x++;
	}
}