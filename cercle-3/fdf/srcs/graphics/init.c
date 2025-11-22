/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:28:45 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 05:12:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	init_render_config(t_render_config *c)
{
	c->render_mode = RENDER_LINES;
	c->use_depth_culling = 0;
	c->fill_triangles = 1;
	c->lod_level = DEFAULT_LOD_LEVEL;
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

	g = malloc(sizeof(t_graphics));
	if (!g)
		return (NULL);
	g->window = args.window;
	g->camera = args.camera;
	g->map = args.map;
	init_render_config(&g->render_config);
	init_frame_data(&g->frame_data);
	return (g);
}
