/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lod.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:30:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Increase LOD and disable tessellation above base density.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the graphics state.
 * @return `1` when processed, otherwise `0`.
 */
int	handle_lod_up(int keycode, t_events *events)
{
	float	current;

	(void)keycode;
	if (!events || !events->graphics)
		return (0);
	current = events->graphics->render_config.lod_value;
	if (current < 32.0f)
		events->graphics->render_config.lod_value *= 2.0f;
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
	events->graphics->needs_refresh = 1;
	return (1);
}

/**
 * @brief Decrease the LOD sampling step toward the base density.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the graphics state.
 * @return `1` when processed, otherwise `0`.
 */
int	handle_lod_down(int keycode, t_events *events)
{
	float	current;

	(void)keycode;
	if (!events || !events->graphics)
		return (0);
	current = events->graphics->render_config.lod_value;
	if (current > 1.0f)
		events->graphics->render_config.lod_value /= 2.0f;
	if (events->graphics->render_config.lod_value < 1.0f)
		events->graphics->render_config.lod_value = 1.0f;
	events->graphics->needs_refresh = 1;
	return (1);
}
