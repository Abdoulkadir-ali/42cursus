/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 09:45:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinder.h"

bool	pf_is_tile_passable(const t_map *map, t_vec2i p, bool doors_are_walls)
{
	char	tile;

	if (!map || p.x < 0 || p.y < 0 || (size_t)p.x >= map->width
		|| (size_t)p.y >= map->height)
		return (false);
	tile = map->grid[p.y][p.x];
	if (tile == '1' || tile == 'm' || tile == 'p' || tile == 's')
		return (false);
	if (tile == '2' || tile == 'O' || tile == 'd' || tile == 'D'
		|| tile == 'e' || tile == 'E')
		return (!doors_are_walls);
	if (ft_strchr("0GMAPNSEW", tile))
		return (true);
	return (false);
}
