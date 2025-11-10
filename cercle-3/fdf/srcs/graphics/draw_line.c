/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:47 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:23:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_bresenham(t_bresenham *b, t_point start, t_point end)
{
	b->dx = abs(end.pos.x - start.pos.x);
	b->dy = abs(end.pos.y - start.pos.y);
	if (start.pos.x < end.pos.x)
		b->sx = 1;
	else
		b->sx = -1;
	if (start.pos.y < end.pos.y)
		b->sy = 1;
	else
		b->sy = -1;
	b->err = b->dx - b->dy;
	b->x = start.pos.x;
	b->y = start.pos.y;
}

static inline void	img_pixel_put_with_z(t_data *data, int x, int y, float z, int color)
{
	char	*dst;

	if (z_buffer_test(data, x, y, z))
	{
		dst = data->img_addr + (y * data->img_line_len + x * (data->img_bpp / 8));
		*(unsigned int *)dst = color;
	}
}

static inline int	is_visible(int x, int y, t_data *data)
{
	return (x >= 0 && x < data->win_width && y >= 0 && y < data->win_height);
}

void	draw_line(t_data *data, t_point start, t_point end)
{
	t_bresenham	b;
	int			color;
	float		total_dist;
	float		current_dist;
	float		z;

	init_bresenham(&b, start, end);
	color = shift_color(start.color, data->camera.color_shift.red,
			data->camera.color_shift.blue, data->camera.color_shift.green);
	total_dist = sqrt((end.pos.x - start.pos.x) * (end.pos.x - start.pos.x) + 
					  (end.pos.y - start.pos.y) * (end.pos.y - start.pos.y));
	while (1)
	{
		if (is_visible(b.x, b.y, data))
		{
			current_dist = sqrt((b.x - start.pos.x) * (b.x - start.pos.x) + 
								(b.y - start.pos.y) * (b.y - start.pos.y));
			z = start.pos.z + (end.pos.z - start.pos.z) * (current_dist / (total_dist + 1e-6));
			img_pixel_put_with_z(data, b.x, b.y, z, color);
		}
		if (b.x == end.pos.x && b.y == end.pos.y)
			break ;
		b.e2 = 2 * b.err;
		if (b.e2 > -b.dy)
		{
			b.err -= b.dy;
			b.x += b.sx;
		}
		if (b.e2 < b.dx)
		{
			b.err += b.dx;
			b.y += b.sy;
		}
	}
}
