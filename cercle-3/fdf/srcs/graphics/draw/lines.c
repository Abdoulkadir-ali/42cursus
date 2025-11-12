/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 23:25:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "graphics.h"
#include "color.h"

static void	init_bresenham(t_bresenham *b, t_point start, t_point end)
{
	b->delta.x = abs((int)end.pos.x - (int)start.pos.x);
	b->delta.y = abs((int)end.pos.y - (int)start.pos.y);
	b->step.x = ((int)start.pos.x < (int)end.pos.x) ? 1 : -1;
	b->step.y = ((int)start.pos.y < (int)end.pos.y) ? 1 : -1;
	b->err = b->delta.x - b->delta.y;
	b->p.x = (int)start.pos.x;
	b->p.y = (int)start.pos.y;
}

int	z_buffer_test(t_graphics *g, int x, int y, float z)
{
	int	index;

	if (!g->render_config.use_depth_culling || !g->window->z_buffer)
		return (1);
	if (x < 0 || x >= g->window->width || y < 0 || y >= g->window->height)
		return (0);
	index = y * g->window->width + x;
	if (z < g->window->z_buffer[index])
	{
		g->window->z_buffer[index] = z;
		return (1);
	}
	return (0);
}

void	img_pixel_put_with_z(t_graphics *g, int x, int y, float z, int color)
{
	char	*dst;

	(void)z;
	// if (z_buffer_test(g, x, y, z))
	{
		dst = g->window->main_img.img_addr + (y * g->window->main_img.img_line_len
				+ x * (g->window->main_img.img_bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_line(t_graphics *g, t_point start, t_point end)
{
	t_bresenham b;
	int color;

	DBG("draw_line start (%d,%d) to (%d,%d)\n", (int)start.pos.x, (int)start.pos.y, (int)end.pos.x, (int)end.pos.y);
	init_bresenham(&b, start, end);
	color = shift_color(start.color, g->camera->color_shift.x,
			g->camera->color_shift.z, g->camera->color_shift.y);
	while (1)
	{
		if (is_visible(b.p.x, b.p.y, g))
			img_pixel_put_with_z(g, b.p.x, b.p.y, 0, color);
		if (b.p.x == (int)end.pos.x && b.p.y == (int)end.pos.y)
			break ;
		b.e2 = 2 * b.err;
		if (b.e2 > -b.delta.y)
		{
			b.err -= b.delta.y;
			b.p.x += b.step.x;
		}
		if (b.e2 < b.delta.x)
		{
			b.err += b.delta.x;
			b.p.y += b.step.y;
		}
	}
	DBG("draw_line end\n");
}