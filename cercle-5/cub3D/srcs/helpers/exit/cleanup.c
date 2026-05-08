/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 23:59:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animation.h"
#include "exit.h"
#include "gameplay.h"
#include "map.h"
#include "window.h"

static void	clear_literal_paths(t_map *map)
{
	map->tex_paths[TEX_DOOR] = NULL;
	map->tex_paths[TEX_DOOR_OPEN] = NULL;
	map->tex_paths[TEX_FLOOR] = NULL;
	map->tex_paths[TEX_CEIL] = NULL;
}

static void	cleanup_world(t_world *world)
{
	if (!world)
		return ;
	anim_mgr_free(world);
	if (world->map)
	{
		clear_literal_paths(world->map);
		free_map(world->map);
		free(world->map);
		world->map = NULL;
	}
	if (world->push_grid)
	{
		free(world->push_grid);
		world->push_grid = NULL;
	}
}

void	cleanup_app(t_app *app)
{
	if (!app)
		return ;
	if (app->world)
		cleanup_world(app->world);
	if (app->window)
		free_window(app->window);
}
