/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XK_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:11 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 16:33:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	init_key_actions(t_key_maps *key_maps)
{
	set_key_actions(key_maps);
	set_key_releases(key_maps);
}

int	key_press(int keycode, t_events *events)
{
	t_key_action	action;
	int				redraw_needed;

	if (keycode >= 0 && keycode < KEY_MAP_SIZE)
	{
		action = events->key_maps.key_actions[keycode];
		if (action)
		{
			redraw_needed = action(keycode, events);
			if (redraw_needed)
				redraw(events);
			return (redraw_needed);
		}
	}
	return (0);
}

int	key_release(int keycode, t_events *events)
{
	t_key_action	action;

	if (keycode >= 0 && keycode < KEY_MAP_SIZE)
	{
		action = events->key_maps.key_releases[keycode];
		if (action)
			return (action(keycode, events));
	}
	return (0);
}

int	loop_hook(t_events *events)
{
	int	needs_redraw;

	calculate_fps(events);
	needs_redraw = 0;
	if (events->camera_manager)
	{
		update_zoom(events->camera_manager);
		if (fabs(events->camera_manager->camera->scale
				- events->camera_manager->camera->target_scale) > 0.001)
			needs_redraw = 1;
	}
	if (process_movement(events))
		needs_redraw = 1;
	if (needs_redraw)
		redraw(events);
	return (0);
}
