/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:35:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/24 01:54:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "generator.h"
#include "graphics.h"

int	handle_g(int keycode, t_events *events)
{
	t_gen_params	params;
	t_map			*new_map;
	int 			idx;

	(void)keycode;
	params.width = events->map->width;
	params.height = events->map->height;
	if (params.width < 50) params.width = 50;
	if (params.height < 50) params.height = 50;
	
	params.scale = 4.0;
	params.z_scale = 20.0;
	params.octaves = 4;
	params.persistence = 0.5;
	params.seed = time(NULL);

	ft_printf("Map regeneration is disabled. Use the Python generator instead.\n");
	return (0);
	// Integrate into Map Manager
	if (events->maps && events->maps->maps && events->maps->count > 0)
	{
		idx = events->maps->current_index;
		// Update map filename to indicate generation
		if (events->maps->map_files)
		{
			if (events->maps->map_files[idx])
				free(events->maps->map_files[idx]);
			events->maps->map_files[idx] = ft_strdup("Generated (Runtime)");
		}
		if (events->maps->maps[idx])
			free_map(events->maps->maps[idx]);
		events->maps->maps[idx] = new_map;
		events->maps->current_map = new_map;
	}
	else
	{
		// Fallback for standalone mode (no manager)
		if (events->graphics->map) // Try to free the active map if it's not managed
			free_map(events->graphics->map);
	}

	// Update global references
	events->map = new_map;
	if (events->graphics)
	{
		cleanup_cache(events->graphics); // Invalidate cache
		events->graphics->map = new_map;
		events->graphics->base_map = new_map; // Update base_map to avoid using freed memory
	}
	if (events->camera_manager)
	{
		events->camera_manager->map = new_map;
		adjust_camera_to_map(events->camera_manager);
		update_rotation_matrix(events->camera_manager->camera);
		calculate_transform_matrix(events->camera_manager->camera);
	}
	events->gui.map = new_map;
	events->graphics->dirty = 1;
	return (0);
}
