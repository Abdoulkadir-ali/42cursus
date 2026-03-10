/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

/**
 * @brief Copy generated heights into a renderable map structure.
 * @param map Destination map.
 * @param heights Source integer heightmap.
 */
static void	fill_map_from_heights(t_map *map, int **heights)
{
	size_t	i;
	t_vec2	pos;
	int		z;

	i = 0;
	pos.y = 0;
	while (pos.y < (int)map->height)
	{
		pos.x = 0;
		while (pos.x < (int)map->width)
		{
			z = heights[pos.y][pos.x];
			map->points.pos[i].x = (double)pos.x;
			map->points.pos[i].y = (double)pos.y;
			map->points.pos[i].z = (double)z;
			map->points.raw[i] = map->points.pos[i];
			map->points.color[i++] = get_solid_color(z);
			pos.x++;
		}
		pos.y++;
	}
}

/**
 * @brief Initialize render metadata and style for a generated map.
 * @param map Generated map to finalize.
 */
static void	setup_map_style(t_map *map)
{
	map->min_proj_z = map->min_max_z.x;
	map->max_proj_z = map->min_max_z.y;
	if (map->max_proj_z - map->min_proj_z > 10.0)
		map->z_divisor = (map->max_proj_z - map->min_proj_z) / 10.0;
	else
		map->z_divisor = 1.0;
	map->style.style = MAP_STYLE_GRADIENT;
	apply_map_style(map);
}

/**
 * @brief Allocate a map and populate it from generated heights.
 * @param params Generation parameters describing dimensions.
 * @param heights Source integer heightmap.
 * @return Allocated renderable map, or `NULL` on failure.
 */
static t_map	*allocate_and_fill_map(t_gen_params params, int **heights)
{
	t_map	*map;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = params.width;
	map->height = params.height;
	if (!allocate_map_points(map))
	{
		free(map);
		return (NULL);
	}
	fill_map_from_heights(map, heights);
	calculate_min_max_z(map);
	calculate_min_max_z(map);
	setup_map_style(map);
	return (map);
}

/**
 * @brief Generate a runtime map from procedural noise parameters.
 * @param params Generation parameters.
 * @return Newly allocated map, or `NULL` on failure.
 */
t_map	*generate_runtime_map(t_gen_params params)
{
	t_map	*map;
	int		**heights;

	heights = generate_heightmap(params);
	if (!heights)
		return (NULL);
	map = allocate_and_fill_map(params, heights);
	free_heightmap(heights, params.height);
	return (map);
}
