/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:20:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/24 00:20:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"
#include "graphics.h"

static void	fill_map_from_heights(t_map *map, int **heights)
{
	size_t	i;
	size_t	x;
	size_t	y;
	int		z;

	i = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			z = heights[y][x];
			map->points.pos[i] = (t_vec3d){(double)x++, (double)y, (double)z};
			map->points.raw[i] = map->points.pos[i];
			map->points.color[i++] = get_solid_color(z);
		}
		y++;
	}
}

t_map	*generate_runtime_map(t_gen_params params)
{
	t_map	*map;
	int		**heights;

	heights = generate_heightmap(params);
	if (!heights)
		return (NULL);
	
	ft_printf("Runtime map generated (%dx%d)\n", params.width, params.height);
	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
	{
		free_heightmap(heights, params.height);
		return (NULL);
	}
	
	map->width = params.width;
	map->height = params.height;
	
	if (!allocate_map_points(map))
	{
		free(map);
		free_heightmap(heights, params.height);
		return (NULL);
	}
	
	fill_map_from_heights(map, heights);
	free_heightmap(heights, params.height);
	
	calculate_min_max_z(map);
	calculate_min_max_z(map);
	map->min_proj_z = map->min_max_z.x;
	map->max_proj_z = map->min_max_z.y;
	if (map->max_proj_z - map->min_proj_z > 10.0)
		map->z_divisor = (map->max_proj_z - map->min_proj_z) / 10.0;
	else
		map->z_divisor = 1.0;
	map->style.style = MAP_STYLE_GRADIENT; // Match loader default?
	apply_map_style(map);
	
	return (map);
}
