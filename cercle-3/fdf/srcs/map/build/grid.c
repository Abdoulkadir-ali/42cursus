/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:28:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 05:12:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "map.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>

static void	init_grid_points(t_map *map)
{
	int	x;
	int	y;
	int	index;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			index = y * map->width + x;
			map->points.raw[index].x = x;
			map->points.raw[index].y = y;
			map->points.raw[index].z = x;
			map->points.pos[index] = map->points.raw[index];
			map->points.color[index] = 0xFFFFFF;
			x++;
		}
		y++;
	}
}

static void	calculate_z_divisor(t_map *map)
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

void	calculate_min_max_z(t_map *map)
{
	int	x;
	int	y;
	int	z;
	int	first;

	first = 1;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			z = map->points.raw[y * map->width + x].z;
			x++;
			if (first)
			{
				map->min_max_z.x = z;
				map->min_max_z.y = z;
				first = 0;
			}
			else
			{
				if (z < map->min_max_z.x)
					map->min_max_z.x = z;
				if (z > map->min_max_z.y)
					map->min_max_z.y = z;
			}
		}
		y++;
	}
	calculate_z_divisor(map);
}

void	calculate_min_max_proj_z(t_map *map, t_camera *camera, double z_divisor)
{
	int		x;
	int		y;
	float	z;
	int		first;
	int		current_x;

	first = 1;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			current_x = x;
			z = project_point(map->points.pos[y * map->width + current_x],
					map->points.color[y * map->width + current_x], camera,
					z_divisor).pos.z;
			if (first)
			{
				map->min_proj_z = z;
				map->max_proj_z = z;
				first = 0;
			}
			else
			{
				if (z < map->min_proj_z)
					map->min_proj_z = z;
				if (z > map->max_proj_z)
					map->max_proj_z = z;
			}
			x++;
		}
		y++;
	}
}

static t_map	*allocate_map_arrays(t_map *map)
{
	int	total;

	total = map->height * map->width;
	map->points.pos = malloc(sizeof(t_vec3d) * total);
	if (!map->points.pos)
		return (NULL);
	map->points.raw = malloc(sizeof(t_vec3d) * total);
	if (!map->points.raw)
		return (NULL);
	map->points.color = malloc(sizeof(int) * total);
	if (!map->points.color)
		return (NULL);
	return (map);
}

t_map	*create_test_grid(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = 50;
	map->height = 50;
	if (!allocate_map_arrays(map))
		return (NULL);
	init_grid_points(map);
	calculate_min_max_z(map);
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
	free(map);
}
