/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:35:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/25 23:19:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "generator.h"

int	handle_g(int keycode, t_events *events)
{
	t_map	*new_map;

	(void)keycode;
	new_map = generate_and_replace_map(events->maps);
	if (!new_map)
		return (0);
	events->map = new_map;
	events->gui.map = new_map;
	if (events->camera_manager)
	{
		events->camera_manager->map = new_map;
		center_camera_on_map(events->camera_manager);
	}
	if (events->graphics)
	{
		if (events->graphics->tesselated_map)
		{
			free_map(events->graphics->tesselated_map);
			events->graphics->tesselated_map = NULL;
		}
		cleanup_cache(events->graphics);
		events->graphics->base_map = new_map;
		events->graphics->map = new_map;
		events->graphics->needs_refresh = 1;
	}
	return (1);
}
