/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:45:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "triangle.h"

static void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	swap_point(t_point *a, t_point *b)
{
	t_point	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	interpolate_color_simple(int c1, int c2, float t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((c1 >> 16) & 0xFF) * (1.0 - t) + ((c2 >> 16) & 0xFF) * t);
	g = (int)(((c1 >> 8) & 0xFF) * (1.0 - t) + ((c2 >> 8) & 0xFF) * t);
	b = (int)((c1 & 0xFF) * (1.0 - t) + (c2 & 0xFF) * t);
	return ((r << 16) | (g << 8) | b);
}


static void	draw_horizontal_scanline_z(t_data *data, int x1, int x2, int y,
		float z1, float z2, int c1, int c2)
{
	int		x;
	int		offset;
	float	t;
	float	z;
	int		color;

	if (x1 > x2)
	{
		ft_swap(&x1, &x2);
		t = z1;
		z1 = z2;
		z2 = t;
		offset = c1;
		c1 = c2;
		c2 = offset;
	}
	if (y < 0 || y >= data->win_height)
		return ;
	x = x1;
	while (x <= x2)
	{
		if (x >= 0 && x < data->win_width)
		{
			t = (x2 == x1) ? 0 : (float)(x - x1) / (float)(x2 - x1);
			z = z1 + t * (z2 - z1);
			color = interpolate_color_simple(c1, c2, t);
			if (z_buffer_test(data, x, y, z))
			{
				offset = (y * data->img_line_len) + (x * (data->img_bpp / 8));
				*(unsigned int *)(data->img_addr + offset) = color;
			}
		}
		x++;
	}
}

static int	interpolate_x(t_point p1, t_point p2, int y)
{
	double	t;

	if (p2.pos.y == p1.pos.y)
		return ((int)p1.pos.x);
	t = (y - p1.pos.y) / (p2.pos.y - p1.pos.y);
	return ((int)(p1.pos.x + t * (p2.pos.x - p1.pos.x)));
}

static float	interpolate_z(t_point p1, t_point p2, int y)
{
	double	t;

	if (p2.pos.y == p1.pos.y)
		return (p1.pos.z);
	t = (y - p1.pos.y) / (p2.pos.y - p1.pos.y);
	return (p1.pos.z + t * (p2.pos.z - p1.pos.z));
}

static int	interpolate_color_edge(t_point p1, t_point p2, int y)
{
	double	t;

	if (p2.pos.y == p1.pos.y)
		return (p1.color);
	t = (y - p1.pos.y) / (p2.pos.y - p1.pos.y);
	return (interpolate_color_simple(p1.color, p2.color, t));
}

void	draw_filled_triangle(t_data *data, t_point p1, t_point p2, t_point p3)
{
	int	y;
	int	x1;
	int	x2;
	int	y_max;

	if (p1.pos.y > p2.pos.y)
		swap_point(&p1, &p2);
	if (p2.pos.y > p3.pos.y)
		swap_point(&p2, &p3);
	if (p1.pos.y > p2.pos.y)
		swap_point(&p1, &p2);
	y = (int)p1.pos.y;
	y_max = (int)p3.pos.y;
	if (y < -10000 || y > 10000 || y_max < -10000 || y_max > 10000)
		return ;
	if (y_max - y > data->win_height * 2)
		return ;
	while (y <= y_max)
	{
		float z1, z2;
		int c1, c2;
		if (y < (int)p2.pos.y)
		{
			x1 = interpolate_x(p1, p3, y);
			x2 = interpolate_x(p1, p2, y);
			z1 = interpolate_z(p1, p3, y);
			z2 = interpolate_z(p1, p2, y);
			c1 = interpolate_color_edge(p1, p3, y);
			c2 = interpolate_color_edge(p1, p2, y);
		}
		else
		{
			x1 = interpolate_x(p1, p3, y);
			x2 = interpolate_x(p2, p3, y);
			z1 = interpolate_z(p1, p3, y);
			z2 = interpolate_z(p2, p3, y);
			c1 = interpolate_color_edge(p1, p3, y);
			c2 = interpolate_color_edge(p2, p3, y);
		}
		draw_horizontal_scanline_z(data, x1, x2, y, z1, z2, c1, c2);
		y++;
	}
}

void	draw_wireframe_triangle(t_data *data, t_point p1, t_point p2, t_point p3)
{
	draw_line(data, p1, p2);
	draw_line(data, p2, p3);
	draw_line(data, p3, p1);
}

void	draw_quad_triangles(t_data *data, t_point p1, t_point p2,
		t_point p3, t_point p4)
{
	if (data->fill_triangles)
	{
		draw_filled_triangle(data, p1, p2, p3);
		draw_filled_triangle(data, p2, p4, p3);
	}
	else
	{
		draw_wireframe_triangle(data, p1, p2, p3);
		draw_wireframe_triangle(data, p2, p4, p3);
	}
}
/*
** Quad layout:
** p1 --- p2
** |  \   |
** |   \  |
** p3 --- p4
**
** Triangle 1: p1, p2, p3
** Triangle 2: p2, p4, p3
*/