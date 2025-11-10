/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:47 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 16:04:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	x;
	int	y;
}	t_bresenham;

static void	init_bresenham(t_bresenham *b, t_point start, t_point end)
{
	b->dx = abs(end.pos.x - start.pos.x);
	b->dy = abs(end.pos.y - start.pos.y);
	b->sx = (start.pos.x < end.pos.x) ? 1 : -1;
	b->sy = (start.pos.y < end.pos.y) ? 1 : -1;
	b->err = b->dx - b->dy;
	b->x = start.pos.x;
	b->y = start.pos.y;
}

static void	img_pixel_put_fast(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_addr + (y * data->img_line_len + x * (data->img_bpp / 8));
	*(unsigned int *)dst = color;
}

static int	is_visible(int x, int y, t_data *data)
{
	return (x >= 0 && x < data->win_width && y >= 0 && y < data->win_height);
}

void	draw_line(t_data *data, t_point start, t_point end)
{
	t_bresenham	b;
	int			color;

	init_bresenham(&b, start, end);
	color = shift_color(start.color, data->camera.color_shift.red,
			data->camera.color_shift.blue, data->camera.color_shift.green);
	while (1)
	{
		if (is_visible(b.x, b.y, data))
			img_pixel_put_fast(data, b.x, b.y, color);
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
