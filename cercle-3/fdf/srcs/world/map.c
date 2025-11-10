#include "fdf.h"
#include <fcntl.h>
#include <stdio.h>

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
	int	first;

	first = 1;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			z = map->points[y][x].pos.z;
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

void	free_map(t_map *map)
{
	int	y;

	if (!map)
		return ;
	if (map->points)
	{
		y = 0;
		while (y < map->height)
		{
			if (map->points[y])
				free(map->points[y]);
			y++;
		}
		free(map->points);
	}
	free(map);
}

t_map	*load_map(char *filename)
{
	t_map	*map;
	FILE	*file;
	char	line[4096];
	int		width;
	int		height;
	int		x;
	int		y;
	char	*token;

	file = fopen(filename, "r");
	if (!file)
		return (create_test_grid());
	width = 0;
	height = 0;
	while (fgets(line, sizeof(line), file))
	{
		if (line[0] == '\n')
			continue ;
		height++;
		if (width == 0)
		{
			token = strtok(line, " \t\n");
			while (token)
			{
				width++;
				token = strtok(NULL, " \t\n");
			}
		}
	}
	if (width == 0 || height == 0)
	{
		fclose(file);
		return (create_test_grid());
	}
	map = malloc(sizeof(t_map));
	if (!map)
	{
		fclose(file);
		return (create_test_grid());
	}
	map->width = width;
	map->height = height;
	map->points = malloc(sizeof(t_point *) * height);
	if (!map->points)
	{
		free(map);
		fclose(file);
		return (create_test_grid());
	}
	y = 0;
	while (y < height)
	{
		map->points[y] = malloc(sizeof(t_point) * width);
		if (!map->points[y])
		{
			free_map(map);
			fclose(file);
			return (create_test_grid());
		}
		x = 0;
		while (x < width)
		{
			map->points[y][x].pos.x = x;
			map->points[y][x].pos.y = y;
			map->points[y][x].pos.z = 0;
			map->points[y][x].color = 0xFFFFFF;
			x++;
		}
		y++;
	}
	rewind(file);
	y = 0;
	while (fgets(line, sizeof(line), file) && y < height)
	{
		if (line[0] == '\n')
			continue ;
		x = 0;
		token = strtok(line, " \t\n");
		while (token && x < width)
		{
			map->points[y][x].pos.x = x;
			map->points[y][x].pos.y = y;
			map->points[y][x].pos.z = atoi(token);
			map->points[y][x].color = 0xFFFFFF;
			x++;
			token = strtok(NULL, " \t\n");
		}
		y++;
	}
	fclose(file);
	calculate_min_max_z(map);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			map->points[y][x].color = get_height_color(
				map->points[y][x].pos.z, map->min_z, map->max_z);
			x++;
		}
		y++;
	}
	return (map);
}
