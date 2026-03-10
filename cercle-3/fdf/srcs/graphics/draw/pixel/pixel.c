/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:30:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/03/10 02:31:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Write one pixel color directly into the image buffer.
 * @param p Pixel write parameters with a resolved destination address.
 */
void	draw_pixel_fast_no_z(t_pixel_draw_params p)
{
	*(unsigned int *)p.pixel_addr = p.color;
}

/**
 * @brief Write one pixel after optional z-buffer depth testing.
 * @param g Graphics state providing render configuration.
 * @param p Pixel write parameters with depth and color information.
 */
void	draw_pixel_fast(t_graphics *g, t_pixel_draw_params p)
{
	if (!g->render_config.use_depth_culling || !p.z_addr || p.zr < *p.z_addr)
	{
		if (g->render_config.use_depth_culling && p.z_addr)
			*p.z_addr = p.zr;
		*(unsigned int *)p.pixel_addr = p.color;
	}
}
