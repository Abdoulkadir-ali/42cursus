/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pw.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 10:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_push_wall	*get_push_wall(t_dda *d, t_map *map)
{
	size_t	idx;
	int		pi;

	if (!map->push_grid_view || !map->push_walls_view)
		return (NULL);
	if (d->map_x < 0 || d->map_y < 0 || (size_t)d->map_x >= map->size.x
		|| (size_t)d->map_y >= map->size.y)
		return (NULL);
	idx = (size_t)d->map_y * map->size.x + (size_t)d->map_x;
	pi = map->push_grid_view[idx];
	if (pi < 0)
		return (NULL);
	return (&((t_push_wall *)map->push_walls_view)[pi]);
}
