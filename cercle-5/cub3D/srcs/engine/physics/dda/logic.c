/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 07:44:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/05 23:31:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "physics.h"

bool	check_cell_content(t_dda *d, t_map *map)
{
	char	c;
	float	t;
	int		side;
	int		pgi;

	c = map->grid[d->map_y][d->map_x];
	pgi = -1;
	if (map->push_grid_view)
		pgi = map->push_grid_view[d->map_y * (int)map->size.x + d->map_x];
	if (pgi >= 0 && push_aabb_hit(d, map, &t, &side))
		return (finalize_axis_hit(d, map), true);
	if (pgi >= 0)
		return (false);
	if (c == '1')
		return (finalize_axis_hit(d, map), true);
	if (is_door_tile(c))
	{
		if (door_open_at(map, d->map_x, d->map_y) >= 1.0f)
			return (false);
		return (finalize_axis_hit(d, map), true);
	}
	return (false);
}

bool	peek_current_cell(t_dda *d, t_map *map)
{
	if (d->map_x < 0 || d->map_y < 0 || (size_t)d->map_x >= map->size.x
		|| (size_t)d->map_y >= map->size.y)
		return (false);
	return (check_cell_content(d, map));
}
