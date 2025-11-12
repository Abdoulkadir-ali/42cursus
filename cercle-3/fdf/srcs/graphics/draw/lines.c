/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 18:31:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "graphics.h"

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

int	z_buffer_test(t_graphics *g, int x, int y, float z)
{
	int	index;

	if (!g->render_config.use_depth_culling || !g->window.z_buffer)
		return (1);
	if (x < 0 || x >= g->window.width || y < 0 || y >= g->window.height)
		return (0);
	index = y * g->window.width + x;
	if (z < g->window.z_buffer[index])
	{
		g->window.z_buffer[index] = z;
		return (1);
	}
	return (0);
}

void	img_pixel_put_with_z(t_graphics *g, int x, int y, float z, int color)
{
	char	*dst;

	if (z_buffer_test(g, x, y, z))
	{
		dst = g->window.main_img.img_addr + (y * g->window.main_img.img_line_len
				+ x * (g->window.main_img.img_bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_line(t_graphics *g, t_point start, t_point end)
{
	t_bresenham b;
	int color;
	float total_dist;
	float current_dist;
	float z;

	init_bresenham(&b, start, end);
	color = shift_color(start.color, g->camera.color_shift.red,
			g->camera.color_shift.blue, g->camera.color_shift.green);
	total_dist = sqrt((end.pos.x - start.pos.x) * (end.pos.x - start.pos.x)
			+ (end.pos.y - start.pos.y) * (end.pos.y - start.pos.y));
	while (1)
	{
		if (is_visible(b.x, b.y, g))
		{
			current_dist = sqrt((b.x - start.pos.x) * (b.x - start.pos.x) + (b.y
						- start.pos.y) * (b.y - start.pos.y));
			z = start.pos.z + (end.pos.z - start.pos.z) * (current_dist
					/ (total_dist + 1e-6));
			img_pixel_put_with_z(g, b.x, b.y, z, color);
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