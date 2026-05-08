/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 10:52:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"

bool	is_active_door_passable(t_world *world, t_dda *d, t_vec2 ray)
{
	char	c;

	(void)ray;
	if (d->map_x < 0 || d->map_y < 0 || (size_t)d->map_x >= world->map->size.x
		|| (size_t)d->map_y >= world->map->size.y)
		return (false);
	c = world->map->grid[d->map_y][d->map_x];
	if (c == 'O' || c == 'e' || c == 'E')
		return (true);
	return (false);
}
