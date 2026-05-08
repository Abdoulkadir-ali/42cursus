/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:44:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	compute_door_axes(t_map *map)
{
	size_t	x;
	size_t	y;
	size_t	idx;

	if (map == NULL || map->grid == NULL)
		return ;
	if (map->door_axis != NULL)
		free(map->door_axis);
	map->door_axis = malloc(map->size.x * map->size.y);
	if (map->door_axis == NULL)
		return ;
	ft_memset(map->door_axis, 0xFF, map->size.x * map->size.y);
	y = 0;
	while (y < map->size.y)
	{
		x = 0;
		while (x < map->size.x)
		{
			idx = y * map->size.x + x;
			if (ft_strchr("2dDeEOD", map->grid[y][x]) != NULL)
				map->door_axis[idx] = 1;
			x++;
		}
		y++;
	}
}
