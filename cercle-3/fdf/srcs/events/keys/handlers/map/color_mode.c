/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:55:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/24 03:06:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "geometry.h"

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
		events->graphics->dirty = 1;
	}
	return (1);
}
