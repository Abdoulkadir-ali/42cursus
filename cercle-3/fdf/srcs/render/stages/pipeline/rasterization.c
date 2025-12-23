/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 17:50:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "graphics.h"

void	rasterization(t_graphics *g)
{
	size_t	i;
	int		height_val;
	__m256i	height_vec;

	clear_frame_buffers(g);
	if (g->render_config.use_horizon_culling && g->horizon_buffer)
	{
		height_val = (int)g->window->height;
		height_vec = _mm256_set1_epi32(height_val);
		i = 0;
		while (i < g->window->width - 7)
		{
			_mm256_storeu_si256((__m256i *)&g->horizon_buffer[i], height_vec);
			i += 8;
		}
		while (i < g->window->width)
			g->horizon_buffer[i++] = height_val;
	}
	cache_projections(g);
	draw_grid(g);
}
