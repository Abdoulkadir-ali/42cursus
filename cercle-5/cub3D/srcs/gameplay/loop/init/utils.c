/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:00:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/07 01:03:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "exit.h"
#include "gameplay.h"

static void	init_world_grids(t_world *world, t_map *map)
{
	size_t	size;

	size = sizeof(int) * map->size.x * map->size.y;
	world->door_grid = malloc(size);
	if (!world->door_grid)
		safe_exit("Out of memory\n", NULL, 1);
	ft_memset(world->door_grid, 0xFF, size);
	map->door_grid_view = world->door_grid;
	world->push_grid = malloc(size);
	if (!world->push_grid)
		safe_exit("Out of memory\n", NULL, 1);
	ft_memset(world->push_grid, 0xFF, size);
	map->push_grid_view = world->push_grid;
	map->push_walls_view = world->push_walls;
	map->active_doors_view = world->active_doors;
}

static void	setup_map_assets(t_map *map)
{
	free(map->tex_paths[TEX_FLOOR]);
	free(map->tex_paths[TEX_CEIL]);
	free(map->tex_paths[TEX_DOOR]);
	free(map->tex_paths[TEX_DOOR_OPEN]);
	map->tex_paths[TEX_FLOOR] = "assets/walls/floor.xpm";
	map->tex_paths[TEX_CEIL] = "assets/walls/ceil.xpm";
	map->tex_paths[TEX_DOOR] = "assets/door/idle/idle0.xpm";
	map->tex_paths[TEX_DOOR_OPEN] = "assets/door/idle_open/open0.xpm";
	map->textures[TEX_DOOR].stretch = true;
	map->textures[TEX_DOOR_OPEN].stretch = true;
}

void	init_gameplay_maps(t_world *world, t_map *tmp_map)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (map == NULL)
		safe_exit("Out of memory\n", NULL, 1);
	*map = *tmp_map;
	world->map = map;
	init_world_grids(world, map);
	setup_map_assets(map);
}
