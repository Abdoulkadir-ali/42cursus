/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 03:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 03:26:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

bool	pf_closed_is_player_walkable(char c)
{
	if (c == '1' || c == ' ' || c == '2')
		return (false);
	return (true);
}

static bool	check_diagonal_tile(t_map *map, size_t x, size_t y)
{
	if (map->grid[y - 1][x - 1] == ' ' || map->grid[y - 1][x + 1] == ' '
		|| map->grid[y + 1][x - 1] == ' ' || map->grid[y + 1][x + 1] == ' ')
		return (false);
	return (true);
}

bool	pf_closed_check_tile(t_map *map, size_t x, size_t y)
{
	if (x == 0 || y == 0 || x == map->width - 1 || y == map->height - 1)
		return (false);
	if (map->grid[y][x - 1] == ' ' || map->grid[y][x + 1] == ' ' || map->grid[y
		- 1][x] == ' ' || map->grid[y + 1][x] == ' ')
		return (false);
	if (!check_diagonal_tile(map, x, y))
		return (false);
	return (true);
}
