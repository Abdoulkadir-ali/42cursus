/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanlines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 13:34:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_horizontal_scanline_z(t_graphics *g, t_scanline_data data)
{
	int		x;
	int		offset;
	float	t;
	float	z;
	int		color;

	if (data.x1 > data.x2)
	{
		ft_swap(&data.x1, &data.x2);
		t = data.z1;
		data.z1 = data.z2;
		data.z2 = t;
		offset = data.c1;
		data.c1 = data.c2;
		data.c2 = offset;
	}
	if (data.y < 0 || data.y >= g->window->height)
		return ;
	x = data.x1;
	while (x <= data.x2)
	{
		if (x >= 0 && x < g->window->width)
		{
			t = (data.x2 == data.x1) ? 0 : (float)(x - data.x1)
				/ (float)(data.x2 - data.x1);
			z = data.z1 + t * (data.z2 - data.z1);
			color = interpolate_color(data.c1, data.c2, t);
			color = shift_color(color, g->camera->color_shift.x,
					g->camera->color_shift.z, g->camera->color_shift.y);
			if (z_buffer_test(g, x, data.y, z))
			{
				offset = (data.y * g->window->main_img.img_line_len) + (x
						* (g->window->main_img.img_bpp / 8));
				*(unsigned int *)(g->window->main_img.img_addr
						+ offset) = color;
			}
		}
		x++;
	}
}