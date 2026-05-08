/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 23:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/05 23:01:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static bool	door_blocks(t_world *world, int gx, int gy, t_vec3 pos)
{
	float	open;

	(void)pos;
	open = door_open_at(world->map, gx, gy);
	return (open <= 0.0f);
}

bool	is_wall(t_world *world, t_vec3 pos)
{
	int		grid_x;
	int		grid_y;
	char	tile;

	if (!world || !world->map || !world->map->grid)
		return (true);
	grid_x = (int)floorf(pos.x);
	grid_y = (int)floorf(pos.y);
	if (grid_x < 0 || grid_y < 0 || (size_t)grid_x >= world->map->width
		|| (size_t)grid_y >= world->map->height)
		return (true);
	tile = world->map->grid[grid_y][grid_x];
	if (tile == '1')
		return (true);
	if (is_door_tile(tile))
		return (door_blocks(world, grid_x, grid_y, pos));
	return (false);
}
