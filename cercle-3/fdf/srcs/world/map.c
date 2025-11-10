#include "fdf.h"

static void	init_flat_pattern(t_map *map)
{
	int	x;
	int	y;

	// Create a checkerboard color pattern on the flat surface
	// so you can see movement clearly
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if ((x + y) % 2 == 0)
				map->points[y][x].color = 0xFFFFFF;
			else
				map->points[y][x].color = 0x888888;
			x++;
		}
		y++;
	}
}

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
			map->points[y][x].pos.x = x;
			map->points[y][x].pos.y = y;
			map->points[y][x].pos.z = 0;
			map->points[y][x].color = 0xFFFFFF;
			x++;
		}
		y++;
	}
}

static void	calculate_min_max_z(t_map *map)
{
	int	x;
	int	y;
	int	z;

	map->min_z = map->points[0][0].pos.z;
	map->max_z = map->points[0][0].pos.z;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			z = map->points[y][x].pos.z;
			if (z < map->min_z)
				map->min_z = z;
			if (z > map->max_z)
				map->max_z = z;
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
	map->points = malloc(sizeof(t_point *) * map->height);
	if (!map->points)
		return (NULL);
	y = 0;
	while (y < map->height)
	{
		map->points[y] = malloc(sizeof(t_point) * map->width);
		if (!map->points[y])
			return (NULL);
		y++;
	}
	init_grid_points(map);
	init_flat_pattern(map);
	calculate_min_max_z(map);
	return (map);
}
