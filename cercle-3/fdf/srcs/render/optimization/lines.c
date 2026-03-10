/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:59:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:21:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Write one pixel into the main image when it passes the depth test.
 * @param g Graphics context owning the image and z-buffer.
 * @param p Screen-space point to write.
 */
void	img_pixel_put_with_z(t_graphics *g, t_point p)
{
	char	*dst;
	t_vec2	v;

	if (!g || !g->window)
		return ;
	if (!g->window->main_img.img_addr)
		return ;
	v = (t_vec2){round(p.pos.x), round(p.pos.y)};
	if (v.x < 0 || v.y < 0 || v.x >= (int)g->window->width
		|| v.y >= (int)g->window->height)
		return ;
	if (!z_buffer_test(g, v, (float)p.pos.z))
		return ;
	dst = g->window->main_img.img_addr + (v.y * g->window->main_img.img_line_len
			+ v.x * (g->window->main_img.img_bpp / 8));
	*(unsigned int *)dst = rgb_to_int(p.color);
}
