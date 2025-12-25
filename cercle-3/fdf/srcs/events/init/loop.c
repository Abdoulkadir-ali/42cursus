/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 22:57:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

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
	if (process_rotation(events))
		needs_redraw = 1;
	if (events->graphics && events->graphics->needs_refresh)
	{
		needs_redraw = 1;
		events->graphics->needs_refresh = 0;
	}
	if (needs_redraw)
		redraw(events);
	return (0);
}
