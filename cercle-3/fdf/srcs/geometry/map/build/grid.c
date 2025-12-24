/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:28:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 00:26:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "geometry.h"

t_map	*create_test_grid(void)
{
	t_map	*map;
	float	min_z;
	float	max_z;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = 50;
	map->height = 50;
	if (!allocate_map_arrays(map))
		return (NULL);
	init_grid_points(map);
	find_min_max_z(map, &min_z, &max_z);
	map->min_max_z.x = min_z;
	map->min_max_z.y = max_z;
	calculate_z_divisor(map);
	map->min_proj_z = map->min_max_z.x;
	map->max_proj_z = map->min_max_z.y;
	return (map);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->points.pos)
		free(map->points.pos);
	if (map->points.raw)
		free(map->points.raw);
	if (map->points.color)
		free(map->points.color);
	if (map->points.source_color)
		free(map->points.source_color);
	free(map);
}
