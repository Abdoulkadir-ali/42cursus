/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:29:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 11:54:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

t_map	*load_map(char *filename)
{
	t_map	*map;
	int		fd;
	int		width;
	int		height;

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
	map->width = width;
	map->height = height;
	if (!allocate_map_points(map))
		return (free_map(map), create_test_grid());
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free_map(map), create_test_grid());
	parse_map_data(map, fd);
	close(fd);
	int y = 0;
	while (y < map->height)
	{
		int x = 0;
		while (x < map->width)
		{
			map->points.pos[y][x] = map->points.raw[y][x];
			x++;
		}
		y++;
	}
	calculate_min_max_z(map);
	map->min_proj_z = map->min_max_z.x;
	map->max_proj_z = map->min_max_z.y;
	map->style.style = MAP_STYLE_GRADIENT;
	apply_map_style(map);
	map->style.style = 0;
	return (map);
}
