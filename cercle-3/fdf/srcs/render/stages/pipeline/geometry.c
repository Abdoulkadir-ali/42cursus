/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 15:28:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

int	calculate_geometry_level(t_graphics *g)
{
	int	level;
	int	min_level_for_mode;

	min_level_for_mode = MIN_DETAIL_LEVEL;
	if (g->render_config.use_adaptive_logic)
	{
		level = calculate_adaptive_level(g);
		if (level > MAX_DETAIL_LEVEL)
			level = MAX_DETAIL_LEVEL;
		if (level < min_level_for_mode)
			level = min_level_for_mode;
		g->render_config.detail_level = level;
	}
	level = g->render_config.detail_level;
	if (level < min_level_for_mode)
	{
		level = min_level_for_mode;
		g->render_config.detail_level = level;
	}
	return (level);
}

void	apply_geometry_mode(t_graphics *g, int level)
{
	g->render_config.use_tesselation = 0;
	g->render_config.lod_value = 1.0f;
	if (level > 0)
	{
		apply_tesselation(g, level);
		g->render_config.lod_value = 1.0f;
	}
	else if (level < 0)
		apply_lod(g, level);
	else
	{
		g->map = g->base_map;
		if (g->tesselated_map)
		{
			free_map(g->tesselated_map);
			g->tesselated_map = NULL;
		}
	}
}

void	geometry_processing(t_graphics *g)
{
	int		level;

	level = calculate_geometry_level(g);
	apply_geometry_mode(g, level);
}
