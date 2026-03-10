/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:29:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:43:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/**
 * @brief Allocate a map structure sized for parsed file contents.
 * @param width Parsed map width.
 * @param height Parsed map height.
 * @return Allocated map, or a fallback test grid on failure.
 */
static t_map	*init_map_structure(size_t width, size_t height)
{
	t_map	*map;

	if (width == 0 || height == 0)
		return (create_test_grid());
	map = malloc(sizeof(t_map));
	if (!map)
		return (create_test_grid());
	map->z_divisor = 1;
	map->width = width;
	map->height = height;
	if (!allocate_map_points(map))
		return (free_map(map), create_test_grid());
	return (map);
}

/**
 * @brief Parse a map file into an already allocated map.
 * @param map Destination map structure.
 * @param filename Path to the map file.
 * @return `0` on success, otherwise `1`.
 */
static int	load_map_data(t_map *map, const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	parse_map_data(map, fd);
	close(fd);
	return (0);
}

/**
 * @brief Finalize a loaded map for rendering.
 * @param map Parsed map to normalize and style.
 */
static void	finalize_map(t_map *map)
{
	size_t	total_size;

	total_size = map->width * map->height;
	ft_memcpy(map->points.pos, map->points.raw, total_size * sizeof(t_vec3d));
	calculate_min_max_z(map);
	map->min_proj_z = map->min_max_z.x;
	map->max_proj_z = map->min_max_z.y;
	if (map->max_proj_z - map->min_proj_z > 10.0)
		map->z_divisor = (unsigned int)((map->max_proj_z - map->min_proj_z)
				/ 10.0 + 0.5);
	else
		map->z_divisor = 1;
	map->style.style = MAP_STYLE_GRADIENT;
	apply_map_style(map);
}

/**
 * @brief Load a map file from disk.
 * @param filename Path to the `.fdf` file.
 * @return Loaded map, or a fallback test grid on failure.
 */
t_map	*load_map(const char *filename)
{
	t_map	*map;
	int		fd;
	size_t	width;
	size_t	height;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Failed to open map file: %s\n", filename);
		return (create_test_grid());
	}
	get_map_dimensions(fd, &width, &height);
	close(fd);
	map = init_map_structure(width, height);
	if (!map)
		return (create_test_grid());
	if (load_map_data(map, filename))
	{
		ft_printf("Error: Failed to load map data: %s\n", filename);
		return (free_map(map), create_test_grid());
	}
	finalize_map(map);
	return (map);
}
