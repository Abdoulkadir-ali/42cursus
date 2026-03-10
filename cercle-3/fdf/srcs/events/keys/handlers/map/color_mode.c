/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:55:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/03/10 03:24:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Toggle the current map style between raw and gradient coloring.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the active map and graphics state.
 * @return `1` when the toggle is applied, otherwise `0`.
 */
int	handle_c(int keycode, t_events *events)
{
	t_map	*map;

	(void)keycode;
	if (!events->map)
		return (0);
	map = events->map;
	if (map->style.style == MAP_STYLE_RAW)
		map->style.style = MAP_STYLE_GRADIENT;
	else
		map->style.style = MAP_STYLE_RAW;
	apply_map_style(map);
	if (events->graphics)
	{
		cleanup_cache(events->graphics);
		events->graphics->needs_refresh = 1;
	}
	return (1);
}
