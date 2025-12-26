/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:30:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/26 15:24:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_pixel_fast_no_z(t_pixel_draw_params p)
{
	*(unsigned int *)p.pixel_addr = p.color;
}

void	draw_pixel_fast(t_graphics *g, t_pixel_draw_params p)
{
	if (!g->render_config.use_depth_culling || !p.z_addr || p.zr < *p.z_addr)
	{
		if (g->render_config.use_depth_culling && p.z_addr)
			*p.z_addr = p.zr;
		*(unsigned int *)p.pixel_addr = p.color;
	}
}

void	img_pixel_put_with_z(t_graphics *g, t_point p)
{
	int					x;
	int					y;
	t_pixel_draw_params	params;

	x = (int)p.pos.x;
	y = (int)p.pos.y;
	if (x < 0 || x >= (int)g->window->width || y < 0
		|| y >= (int)g->window->height)
		return ;
	params.pixel_addr = g->window->main_img.img_addr
		+ (y * g->window->main_img.img_line_len
			+ x * (g->window->main_img.img_bpp / 8));
	params.z_addr = NULL;
	if (g->window->z_buffer)
		params.z_addr = &g->window->z_buffer[y * g->window->width + x];
	params.zr = p.pos.z;
	params.color = (p.color.x << 16) | (p.color.y << 8) | p.color.z;
	draw_pixel_fast(g, params);
}
