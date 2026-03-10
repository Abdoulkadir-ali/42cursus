/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 02:12:48 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

/**
 * @brief Allocate a 2D integer heightmap.
 * @param height Number of rows.
 * @param width Number of columns.
 * @return Allocated heightmap, or `NULL` on failure.
 */
int	**allocate_map(int height, int width)
{
	int		**map;
	t_vec2	pos;

	map = (int **)malloc(sizeof(int *) * height);
	if (!map)
		return (NULL);
	pos.y = 0;
	while (pos.y < height)
	{
		map[pos.y] = (int *)malloc(sizeof(int) * width);
		if (!map[pos.y])
		{
			while (pos.y >= 0)
				free(map[pos.y--]);
			free(map);
			return (NULL);
		}
		pos.y++;
	}
	return (map);
}

/**
 * @brief Free a 2D integer heightmap.
 * @param map Heightmap to release.
 * @param height Number of rows allocated in the map.
 */
void	free_heightmap(int **map, int height)
{
	t_vec2	pos;

	if (!map)
		return ;
	pos.y = 0;
	while (pos.y < height)
	{
		free(map[pos.y]);
		pos.y++;
	}
	free(map);
}
