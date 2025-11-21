/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:53:06 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 22:30:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <stdlib.h>

void	init_mouse(t_mouse *mouse)
{
	mouse->left_pressed = 0;
	mouse->right_pressed = 0;
	mouse->middle_pressed = 0;
	mouse->last_x = 0;
	mouse->last_y = 0;
	mouse->middle_start_x = 0;
	mouse->middle_start_y = 0;
}

void	init_keys(t_keys *keys)
{
	keys->up = 0;
	keys->down = 0;
	keys->left = 0;
	keys->right = 0;
	keys->ctrl_left = 0;
	keys->ctrl_right = 0;
	keys->shift_left = 0;
	keys->shift_right = 0;
	keys->l = 0;
	keys->z = 0;
	keys->f = 0;
	keys->h = 0;
	keys->d = 0;
	keys->t = 0;
	keys->s = 0;
	keys->a = 0;
	keys->x = 0;
	keys->i = 0;
	keys->v = 0;
	keys->g = 0;
}

static void init_events_graphics(t_events *events)
{
	if (events->graphics)
	{
		events->render_mode = events->graphics->render_config.render_mode;
		events->lod_level = events->graphics->render_config.lod_level;
		events->use_depth_culling = events->graphics->render_config.use_depth_culling;
		events->fill_triangles = events->graphics->render_config.fill_triangles;
	}
	else
	{
		events->render_mode = 0;
		events->lod_level = DEFAULT_LOD_LEVEL;
		events->use_depth_culling = 1;
		events->fill_triangles = 0;
	}
}

t_events	*init_events(t_events_args *args)
{
    t_events    *events;

    events = malloc(sizeof(t_events));
    if (!events)
        return (NULL);
    events->window = args->window;
    events->graphics = args->graphics;
    events->gui = args->gui;
	events->camera_manager = args->camera_manager;
	events->camera = args->camera_manager ? args->camera_manager->camera : NULL;
    events->maps = args->maps;
	events->map = args->map;
	init_events_graphics(events);
	init_mouse(&events->mouse);
	init_keys(&events->keys);
    init_key_actions(&events->key_maps);
    return (events);
}