/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 17:50:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "graphics.h"

float	calculate_zoom_bias(float raw_log)
{
	if (raw_log > 0)
	{
		if (raw_log > 0.5f)
			return ((raw_log - 0.5f) * 2.0f);
		return (0.0f);
	}
	return (raw_log * 1.0f);
}

int	calculate_adaptive_level(t_graphics *g)
{
	float	base_scale;
	float	ratio;
	float	base_pts;
	float	ideal;

	if (g->base_map->width > 0)
		base_scale = (float)g->window->width / (g->base_map->width * 1.5);
	else
		base_scale = 1.0f;
	if (base_scale < 0.0001f)
		base_scale = 0.0001f;
	ratio = g->camera->scale / base_scale;
	if (ratio < 0.0001f)
		ratio = 0.0001f;
	base_pts = (float)(g->base_map->width * g->base_map->height);
	if (base_pts < 1.0f)
		base_pts = 1.0f;
	ideal = (log2f((float)g->render_config.target_tesselation_points / base_pts)
			* 0.5f) + calculate_zoom_bias(log2f(ratio));
	return ((int)roundf(ideal));
}
