/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:59:50 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 15:24:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

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
