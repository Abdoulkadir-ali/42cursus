/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:29:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:48:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "map.h"

t_map	*load_map(char *filename)
{
	t_map	*map;
	int		fd;
	int		width;
	int		height;
	clock_t	start;
	clock_t	end;
	size_t	total_size;

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
	/* REPLACE THE NESTED WHILE LOOPS WITH THIS: */
	/* Bulk copy raw data to pos data (Instant) */
	total_size = (size_t)map->width * (size_t)map->height;
	ft_memcpy(map->points.pos, map->points.raw, total_size * sizeof(t_vec3d));
	/* ---------------------------------------- */
	calculate_min_max_z(map);
	map->min_proj_z = map->min_max_z.x;
	map->max_proj_z = map->min_max_z.y;
	map->style.style = MAP_STYLE_GRADIENT;
	apply_map_style(map);
	map->style.style = 0;
	return (map);
}
