/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesselation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 23:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/17 23:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "graphics.h"

int	handle_t(int keycode, t_events *events)
{
	(void)keycode;
	if (!events || !events->graphics)
		return (0);
	events->graphics->render_config.use_tesselation = !events->graphics->render_config.use_tesselation;
	return (1);
}

int	handle_bracket(int keycode, t_events *events)
{
	if (!events || !events->graphics) return (0);
	handle_tesselation_points(keycode, events->graphics);
	return (1);
}


int	handle_j(int keycode, t_events *events)
{
	(void)keycode;
	if (!events || !events->graphics)
		return (0);
	events->graphics->render_config.use_horizon_culling = !events->graphics->render_config.use_horizon_culling;
	return (1);
}

int	handle_tesselation_up(int keycode, t_events *events)
{
	(void)keycode;
	// Invalidate existing tessellated map to force regeneration
	if (events->graphics->tesselated_map)
	{
		free_map(events->graphics->tesselated_map);
		events->graphics->tesselated_map = NULL;
	}
	// Force tessellation on if leveling up?
	if (!events->graphics->render_config.use_tesselation)
		events->graphics->render_config.use_tesselation = 1;

	return (1);
}

int	handle_tesselation_down(int keycode, t_events *events)
{
	(void)keycode;
	if (!events || !events->graphics)
		return (0);
	
	int current = events->graphics->render_config.tesselation_level;
	
	if (current > 1)
		events->graphics->render_config.tesselation_level--;
	
	// Invalidate
	if (events->graphics->tesselated_map)
	{
		free_map(events->graphics->tesselated_map);
		events->graphics->tesselated_map = NULL;
	}

	return (1);
}

int	handle_lod_up(int keycode, t_events *events)
{
	(void)keycode;
	if (!events || !events->graphics) return (0);
	
	// Increase LOD value (more skip = less detail)
	// Or should "LOD Up" mean "Better Quality"? 
	// Usually "Increase LOD Level" means "Less Detail" (Level 0=Full, Level 1=Half).
	// Let's stick to numerical: LOD value goes up (1 -> 2 -> 4).
	
	float current = events->graphics->render_config.lod_value;
	if (current < 32.0f)
		events->graphics->render_config.lod_value *= 2.0f;
		
	// If LOD > 1, disable Tesselation
	if (events->graphics->render_config.lod_value > 1.05f)
	{
		events->graphics->render_config.use_tesselation = 0;
		if (events->graphics->tesselated_map)
		{
			free_map(events->graphics->tesselated_map);
			events->graphics->tesselated_map = NULL;
			events->graphics->map = events->graphics->base_map;
		}
	}
	events->graphics->dirty = 1; // Mark dirty
	return (1);
}

int	handle_lod_down(int keycode, t_events *events)
{
	(void)keycode;
	if (!events || !events->graphics) return (0);

	float current = events->graphics->render_config.lod_value;
	if (current > 1.0f)
		events->graphics->render_config.lod_value /= 2.0f;
		
	if (events->graphics->render_config.lod_value < 1.0f)
		events->graphics->render_config.lod_value = 1.0f;
		
	events->graphics->dirty = 1; // Mark dirty
	return (1);
}
