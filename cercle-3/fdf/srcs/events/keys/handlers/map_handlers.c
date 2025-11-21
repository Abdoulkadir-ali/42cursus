/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 21:13:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <stdio.h>

int	handle_escape(int keycode, t_events *events)
{
	(void)keycode;
	
	return (cleanup_and_exit(events));
}

int	handle_r(int keycode, t_events *events)
{
	(void)keycode;
	
	reset_view(events);
	reset_style(events->camera);
	return (1);
}

int	handle_n(int keycode, t_events *events)
{
	(void)keycode;
	/* cycle the map list, update event and camera pointers, reset view */
	cycle_map(events->maps);
	if (events->maps)
	{
		events->map = events->maps->current_map;
		if (events->camera_manager)
			events->camera_manager->map = events->maps->current_map;
	}
	reset_view(events);
	return (1);
}

int	handle_s(int keycode, t_events *events)
{
	(void)keycode;
	
	cycle_gui_style(events->gui);
	return (1);
}

int	handle_a(int keycode, t_events *events)
{
	(void)keycode;
	
	events->render_mode = (events->render_mode + 1) % RENDER_MODE_COUNT;
	return (1);
}