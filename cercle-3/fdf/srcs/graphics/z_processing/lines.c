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
#include <stdio.h>

void	img_pixel_put_with_z(t_graphics *g, int x, int y, float z, int color)
{
	char	*dst;

	/* defensive checks to avoid out-of-bounds writes */
	(void)z;
	if (!g || !g->window)
		return ;
	if (!g->window->main_img.img_addr)
	{
		printf("[diag] img_pixel_put_with_z: no img_addr, skip (%d,%d)\n", x, y);
		return ;
	}
	if (x < 0 || y < 0 || x >= g->window->width || y >= g->window->height)
	{
		printf("[diag] img_pixel_put_with_z: out-of-bounds write skipped x=%d y=%d w=%d h=%d\n",
			x, y, g->window->width, g->window->height);
		return ;
	}

	dst = g->window->main_img.img_addr + (y * g->window->main_img.img_line_len
			+ x * (g->window->main_img.img_bpp / 8));
	*(unsigned int *)dst = color;
}
