/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:11:34 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 00:26:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

void	init_grid_points(t_map *map)
{
	t_vec2	pos;
	size_t	idx;

	pos.y = 0;
	while (pos.y < (int)map->height)
	{
		pos.x = 0;
		while (pos.x < (int)map->width)
		{
			idx = (size_t)pos.y * map->width + pos.x;
			map->points.raw[idx].x = pos.x;
			map->points.raw[idx].y = pos.y;
			map->points.raw[idx].z = pos.x;
			map->points.pos[idx] = map->points.raw[idx];
			map->points.color[idx] = 0xFFFFFF;
			pos.x++;
		}
		pos.y++;
	}
}

void	calculate_z_divisor(t_map *map)
{
	if (map->min_max_z.y - map->min_max_z.x > 50)
		map->z_divisor = (map->min_max_z.y - map->min_max_z.x) / 10.0;
	else
		map->z_divisor = 1.0;
	if (abs(map->min_max_z.y) > abs(map->min_max_z.x))
		map->z_divisor = abs(map->min_max_z.y) / 10.0;
	else
		map->z_divisor = abs(map->min_max_z.x) / 10.0;
	if (map->z_divisor < 1.0)
		map->z_divisor = 1.0;
}

t_map	*allocate_map_arrays(t_map *map)
{
	size_t	total;

	total = (size_t)map->width * (size_t)map->height;
	map->points.pos = malloc(sizeof(t_vec3d) * total);
	map->points.raw = malloc(sizeof(t_vec3d) * total);
	map->points.color = malloc(sizeof(int) * total);
	if (!map->points.pos || !map->points.raw || !map->points.color)
		return (NULL);
	return (map);
}
