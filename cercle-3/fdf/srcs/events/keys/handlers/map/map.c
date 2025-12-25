/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 23:02:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	handle_r(int keycode, t_events *events)
{
	(void)keycode;
	events->camera->target_rotation = create_vec3d(35.264 * M_PI / 180.0, 0.0,
			45.0 * M_PI / 180.0);
	reset_view(events);
	reset_style(events->camera);
	return (1);
}

int	handle_n(int keycode, t_events *events)
{
	(void)keycode;
	cycle_map(events->maps);
	if (events->maps)
	{
		events->map = events->maps->current_map;
		if (events->camera_manager)
			events->camera_manager->map = events->maps->current_map;
		if (events->graphics)
		{
			events->graphics->base_map = events->maps->current_map;
			events->graphics->map = events->maps->current_map;
			events->graphics->needs_refresh = 1;
		}
		events->gui.map = events->maps->current_map;
	}
	center_camera_on_map(events->camera_manager);
	return (1);
}

int	handle_s(int keycode, t_events *events)
{
	(void)keycode;
	cycle_gui_style(&events->gui);
	return (1);
}

int	handle_k(int keycode, t_events *events)
{
	(void)keycode;
	events->render_mode = (events->render_mode + 1) % RENDER_MODE_COUNT;
	if (events->graphics)
		events->graphics->needs_refresh = 1;
	return (1);
}
