/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:24:22 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 15:43:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_events	*init_events(t_data *data)
{
	t_events	*events;

	events = malloc(sizeof(t_events));
	if (!events)
		return (NULL);
	events->window = data->window;
	events->graphics = data->graphics;
	events->gui = data->gui;
	events->camera_ctx = data->camera_ctx;
	events->maps = &data->maps;
	events->map = data->maps.current_map;
	events->render_mode = data->graphics->render_config.render_mode;
	events->lod_level = data->graphics->render_config.lod_level;
	events->use_depth_culling = data->graphics->render_config.use_depth_culling;
	events->fill_triangles = data->graphics->render_config.fill_triangles;
	init_mouse(&events->mouse);
	init_keys(&events->keys);
	return (events);
}