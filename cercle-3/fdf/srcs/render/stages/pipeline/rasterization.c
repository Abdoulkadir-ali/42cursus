/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 15:50:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "graphics.h"

void	rasterization(t_graphics *g)
{
	size_t	i;
	int		height_val;

	clear_frame_buffers(g);
	if (g->render_config.use_horizon_culling && g->horizon_buffer)
	{
		height_val = (int)g->window->height;
		i = 0;
		while (i < g->window->width)
			g->horizon_buffer[i++] = height_val;
	}
	cache_projections(g);
	draw_grid(g);
}
