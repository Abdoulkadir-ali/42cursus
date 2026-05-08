/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 03:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 03:28:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

bool	pf_closed_check_sprite_cells(t_map *map)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == '2' && !pf_closed_check_tile(map, x, y))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	pf_closed_check_hborders(t_map *map)
{
	size_t	x;

	x = 0;
	while (x < map->width)
	{
		if (pf_closed_is_player_walkable(map->grid[0][x])
			|| pf_closed_is_player_walkable(map->grid[map->height - 1][x]))
			return (false);
		x++;
	}
	return (true);
}
