/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 00:26:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	z_buffer_test(t_graphics *g, int x, int y, float z)
{
	int			index;
	t_window	*w;

	w = g->window;
	if (!g->render_config.use_depth_culling || !w->z_buffer)
		return (1);
	if (x < 0 || x >= (int)w->width || y < 0 || y >= (int)w->height)
		return (0);
	index = (size_t)y * w->width + (size_t)x;
	if (z < w->z_buffer[index])
	{
		w->z_buffer[index] = z;
		return (1);
	}
	return (0);
}
