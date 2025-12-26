/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:28:45 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 15:29:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	init_render_config(t_render_config *c)
{
	c->render_mode = RENDER_LINES;
	c->use_depth_culling = 1;
	c->lod_value = DEFAULT_LOD_LEVEL;
	c->use_tesselation = 1;
	c->tesselation_level = 1;
	c->max_tesselation_level = 5;
	c->use_horizon_culling = 0;
	c->use_adaptive_logic = 1;
	c->target_tesselation_points = DEFAULT_TARGET_POINTS;
	c->detail_level = 0;
	c->last_tess_level = -100;
	c->last_tess_min = (t_vec2){-1, -1};
	c->last_tess_max = (t_vec2){-1, -1};
}

void	init_frame_data(t_frame_data *f)
{
	f->last_frame_time = 0;
	f->frame_in_progress = 0;
	f->fps = 0;
	f->frame_count = 0;
	f->last_check = 0;
}

t_graphics	*init_graphics(t_graphics_args args)
{
	t_graphics	*g;
	int			i;

	g = malloc(sizeof(t_graphics));
	if (!g)
		return (NULL);
	g->window = args.window;
	g->camera = args.camera;
	g->base_map = args.map;
	g->tesselated_map = NULL;
	i = 0;
	while (i < 8)
		g->lod_maps[i++] = NULL;
	g->map = args.map;
	g->cache = (t_cache){NULL, 0, 0, NULL, 0, {{0, 0, 0}, {0, 0, 0}, 0, 0, 0}};
	g->needs_refresh = 1;
	g->horizon_buffer = malloc(sizeof(int) * g->window->width);
	if (!g->horizon_buffer)
	{
		free(g);
		return (NULL);
	}
	init_render_config(&g->render_config);
	init_frame_data(&g->frame_data);
	return (g);
}
