/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:53:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:30:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Copy the initial graphics render settings into the event snapshot.
 * @param e Event context to initialize.
 */
static void	init_events_graphics(t_events *e)
{
	if (e->graphics)
	{
		e->render_mode = e->graphics->render_config.render_mode;
		e->lod_value = e->graphics->render_config.lod_value;
		e->use_depth_culling = e->graphics->render_config.use_depth_culling;
		e->filled = e->graphics->render_config.filled;
	}
	else
	{
		e->render_mode = 0;
		e->lod_value = DEFAULT_LOD_LEVEL;
		e->use_depth_culling = 1;
		e->filled = 0;
	}
}

/**
 * @brief Allocate and initialize the runtime event context.
 * @param args Shared runtime pointers used by the event system.
 * @return Newly allocated event context, or `NULL` on failure.
 */
t_events	*init_events(t_events_args *args)
{
	t_events	*e;

	e = ft_calloc(1, sizeof(t_events));
	if (!e)
		return (NULL);
	e->window = args->window;
	e->graphics = args->graphics;
	e->gui = *args->gui;
	e->camera_manager = args->camera_manager;
	if (args->camera_manager)
		e->camera = args->camera_manager->camera;
	else
		e->camera = NULL;
	e->maps = args->maps;
	e->map = args->map;
	init_events_graphics(e);
	init_mouse(&e->mouse);
	init_keys(&e->keys);
	set_key_actions(&e->key_maps);
	set_key_releases(&e->key_maps);
	return (e);
}
