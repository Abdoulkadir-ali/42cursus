/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/05 21:21:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	free_raw(char **raw, size_t count)
{
	size_t	i;

	if (raw == NULL)
		return ;
	i = 0;
	while (i < count)
		free(raw[i++]);
	free(raw);
}

static void	free_grid(t_map *map)
{
	size_t	i;

	if (map->grid == NULL)
		return ;
	i = 0;
	while (i < map->height)
		free(map->grid[i++]);
	free(map->grid);
	map->grid = NULL;
}

static void	free_tex_paths(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (map->tex_paths[i] != NULL)
		{
			free(map->tex_paths[i]);
			map->tex_paths[i] = NULL;
		}
		i++;
	}
}

void	free_map(t_map *map)
{
	if (map == NULL)
		return ;
	free_grid(map);
	free_tex_paths(map);
	if (map->portal_pair != NULL)
	{
		free(map->portal_pair);
		map->portal_pair = NULL;
	}
	if (map->door_axis != NULL)
	{
		free(map->door_axis);
		map->door_axis = NULL;
	}
}
