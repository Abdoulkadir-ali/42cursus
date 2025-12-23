/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesselation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:05:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

static void	set_tesselation_level(t_graphics *g, int level)
{
	g->render_config.use_tesselation = 1;
	g->render_config.tesselation_level = level;
	if (g->render_config.tesselation_level > MAX_DETAIL_LEVEL)
		g->render_config.tesselation_level = MAX_DETAIL_LEVEL;
}

static int	is_tesselation_cache_valid(t_graphics *g, t_vec2 min, t_vec2 max)
{
	return (g->tesselated_map
		&& g->render_config.last_tess_level
		== g->render_config.tesselation_level
		&& g->render_config.last_tess_min.x == min.x
		&& g->render_config.last_tess_min.y == min.y
		&& g->render_config.last_tess_max.x == max.x
		&& g->render_config.last_tess_max.y == max.y);
}

static void	update_tesselated_map(t_graphics *g, t_vec2 min, t_vec2 max)
{
	if (g->tesselated_map)
		free_map(g->tesselated_map);
	g->tesselated_map = generate_tesselated_submap(g->base_map, min, max,
			g->render_config.tesselation_level);
	if (g->tesselated_map)
	{
		g->map = g->tesselated_map;
		g->render_config.last_tess_level = g->render_config.tesselation_level;
		g->render_config.last_tess_min = min;
		g->render_config.last_tess_max = max;
	}
	else
	{
		g->map = g->base_map;
		g->render_config.use_tesselation = 0;
		g->render_config.last_tess_level = -100;
	}
}

void	apply_tesselation(t_graphics *g, int level)
{
	t_vec2	min;
	t_vec2	max;

	set_tesselation_level(g, level);
	min = (t_vec2){0, 0};
	max = (t_vec2){g->base_map->width, g->base_map->height};
	get_visible_map_bounds(g, &min, &max);
	if (is_tesselation_cache_valid(g, min, max))
	{
		g->map = g->tesselated_map;
		return ;
	}
	update_tesselated_map(g, min, max);
}
