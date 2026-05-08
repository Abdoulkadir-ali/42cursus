/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/05 22:05:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "gameplay.h"

bool	is_door_tile(char c)
{
	return (c == '2' || c == 'd' || c == 'D'
		|| c == 'O' || c == 'e' || c == 'E');
}

bool	is_door_open_tile(char c)
{
	return (c == 'O' || c == 'e' || c == 'E');
}

float	door_open_at(t_map *map, int mx, int my)
{
	int						idx;
	t_door_anim_instance	*doors;
	char					c;

	if (!map || mx < 0 || my < 0
		|| (size_t)mx >= map->size.x || (size_t)my >= map->size.y)
		return (0.0f);
	if (map->door_grid_view && map->active_doors_view)
	{
		idx = map->door_grid_view[(size_t)my * map->size.x + (size_t)mx];
		if (idx >= 0)
		{
			doors = (t_door_anim_instance *)map->active_doors_view;
			return (doors[idx].open_amount);
		}
	}
	c = map->grid[my][mx];
	if (is_door_open_tile(c))
		return (1.0f);
	return (0.0f);
}
