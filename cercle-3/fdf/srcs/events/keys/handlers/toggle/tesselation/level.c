/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:24:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Enable tessellation and clear any existing tessellated map cache.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the graphics state.
 * @return Always `1` after applying the change.
 */
int	handle_tesselation_up(int keycode, t_events *events)
{
	(void)keycode;
	if (events->graphics->tesselated_map)
	{
		free_map(events->graphics->tesselated_map);
		events->graphics->tesselated_map = NULL;
	}
	if (!events->graphics->render_config.use_tesselation)
		events->graphics->render_config.use_tesselation = 1;
	return (1);
}

/**
 * @brief Decrease the tessellation level and clear any cached tessellated map.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the graphics state.
 * @return `1` when processed, otherwise `0`.
 */
int	handle_tesselation_down(int keycode, t_events *events)
{
	int	current;

	(void)keycode;
	if (!events || !events->graphics)
		return (0);
	current = events->graphics->render_config.tesselation_level;
	if (current > 1)
		events->graphics->render_config.tesselation_level--;
	if (events->graphics->tesselated_map)
	{
		free_map(events->graphics->tesselated_map);
		events->graphics->tesselated_map = NULL;
	}
	return (1);
}
