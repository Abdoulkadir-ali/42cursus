/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 13:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	img_pixel_put_with_z(t_graphics *g, int x, int y, float z, int color)
{
	char    *dst;

	if (!g || !g->window)
		return ;
	if (!g->window->main_img.img_addr)
		return ;
	if (x < 0 || y < 0 || x >= g->window->width || y >= g->window->height)
		return ;

	/* perform z-buffer test (triangles.c provides z_buffer_test) */
	if (!z_buffer_test(g, x, y, z))
		return ;

	dst = g->window->main_img.img_addr + (y * g->window->main_img.img_line_len
			+ x * (g->window->main_img.img_bpp / 8));
	*(unsigned int *)dst = color;
}
