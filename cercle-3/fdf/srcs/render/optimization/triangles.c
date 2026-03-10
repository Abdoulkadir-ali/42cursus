/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:21:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/**
 * @brief Test one fragment against the z-buffer and update it on success.
 * @param g Graphics context owning the window depth buffer.
 * @param v Integer screen-space pixel coordinates.
 * @param z Depth value to compare against the stored depth.
 * @return `1` when the fragment should be drawn, otherwise `0`.
 */
int	z_buffer_test(t_graphics *g, t_vec2 v, float z)
{
	int			index;
	t_window	*w;

	w = g->window;
	if (!g->render_config.use_depth_culling || !w->z_buffer)
		return (1);
	if (v.x < 0 || v.x >= (int)w->width || v.y < 0 || v.y >= (int)w->height)
		return (0);
	index = (size_t)v.y * w->width + (size_t)v.x;
	if (z < w->z_buffer[index])
	{
		w->z_buffer[index] = z;
		return (1);
	}
	return (0);
}
