/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:29:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 13:04:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map.h"
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

t_map	*load_map(char *filename)
{
	t_map	*map;
	int		fd;
	int		width;
	int		height;
	clock_t	start;
	clock_t	end;

	start = clock();
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (create_test_grid());
	get_map_dimensions(fd, &width, &height);
	close(fd);
	if (width == 0 || height == 0)
		return (create_test_grid());
	map = malloc(sizeof(t_map));
	if (!map)
		return (create_test_grid());
	/* ensure z_divisor is initialized to a safe default to avoid garbage dividing */
	map->z_divisor = 1.0;
	map->width = width;
	map->height = height;
	if (!allocate_map_points(map))
		return (free_map(map), create_test_grid());
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free_map(map), create_test_grid());
	parse_map_data(map, fd);
	close(fd);
	end = clock();
	printf("Parsing time: %f seconds\n", (double)(end - start)
		/ CLOCKS_PER_SEC);
	
	/* REVERT: Manual 2D Copy */
	int x, y_idx;
	y_idx = 0;
	while (y_idx < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->points.pos[y_idx][x] = map->points.raw[y_idx][x];
			x++;
		}
		y_idx++;
	}
	/* ---------------------- */
	
	calculate_min_max_z(map);
	map->min_proj_z = map->min_max_z.x;
	map->max_proj_z = map->min_max_z.y;
	map->style.style = MAP_STYLE_GRADIENT;
	apply_map_style(map);
	map->style.style = 0;
	return (map);
}
