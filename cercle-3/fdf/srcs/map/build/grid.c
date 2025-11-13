/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:28:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 02:19:01 by abdoali          ###   ########.fr       */
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

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->points.raw[y][x].x = x;
			map->points.raw[y][x].y = y;
			map->points.raw[y][x].z = x;
			map->points.pos[y][x] = map->points.raw[y][x];
			map->points.color[y][x] = 0xFFFFFF;
			x++;
		}
		y++;
	}
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
			z = map->points.raw[y][x].z;
			if (first)
			{
				map->min_z = z;
				map->max_z = z;
				first = 0;
			}
			else
			{
				if (z < map->min_z)
					map->min_z = z;
				if (z > map->max_z)
					map->max_z = z;
			}
			x++;
		}
		y++;
	}
	if (map->max_z - map->min_z > 50)
		map->z_divisor = (map->max_z - map->min_z) / 10.0;
	else
		map->z_divisor = 1.0;
	// Clamp z_divisor to prevent extreme normalization
	map->z_divisor = (abs(map->max_z) > abs(map->min_z) ? abs(map->max_z) : abs(map->min_z))
		/ 10.0;
	if (map->z_divisor < 1.0)
		map->z_divisor = 1.0;
}

void	calculate_min_max_proj_z(t_map *map, t_camera *camera,
		t_projection_type projection, double z_divisor)
{
	int		x;
	int		y;
	float	z;
	int		first;
	t_point	p;

	first = 1;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			p = project_point(map->points.pos[y][x],
					map->points.color[y][x], camera, projection,
					z_divisor);
			z = p.pos.z;
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

t_map	*create_test_grid(void)
{
	t_map	*map;
	int		y;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = 50;
	map->height = 50;
	map->points.pos = malloc(sizeof(t_vec3d *) * map->height);
	if (!map->points.pos)
		return (NULL);
	map->points.raw = malloc(sizeof(t_vec3d *) * map->height);
	if (!map->points.raw)
		return (NULL);
	map->points.color = malloc(sizeof(int *) * map->height);
	if (!map->points.color)
		return (NULL);
	y = 0;
	while (y < map->height)
	{
		map->points.pos[y] = malloc(sizeof(t_vec3d) * map->width);
		if (!map->points.pos[y])
			return (NULL);
		map->points.raw[y] = malloc(sizeof(t_vec3d) * map->width);
		if (!map->points.raw[y])
			return (NULL);
		map->points.color[y] = malloc(sizeof(int) * map->width);
		if (!map->points.color[y])
			return (NULL);
		y++;
	}
	init_grid_points(map);
	calculate_min_max_z(map);
	map->min_proj_z = map->min_z;
	map->max_proj_z = map->max_z;
	return (map);
}

void	free_map(t_map *map)
{
	int	y;

	if (!map)
		return ;
	if (map->points.pos)
	{
		y = 0;
		while (y < map->height)
		{
			if (map->points.pos[y])
				free(map->points.pos[y]);
			if (map->points.raw[y])
				free(map->points.raw[y]);
			if (map->points.color[y])
				free(map->points.color[y]);
			y++;
		}
		free(map->points.pos);
		free(map->points.raw);
		free(map->points.color);
	}
	free(map);
}
