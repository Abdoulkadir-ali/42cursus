/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 09:36:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"

static void	update_grid_char(t_world *world, t_vec2s pos, char c, bool opening)
{
	if (opening)
	{
		if (c == '2')
			world->map->grid[pos.y][pos.x] = 'O';
		else if (c == 'd')
			world->map->grid[pos.y][pos.x] = 'e';
		else if (c == 'D')
			world->map->grid[pos.y][pos.x] = 'E';
	}
	else
	{
		if (c == 'O')
			world->map->grid[pos.y][pos.x] = '2';
		else if (c == 'e')
			world->map->grid[pos.y][pos.x] = 'd';
		else if (c == 'E')
			world->map->grid[pos.y][pos.x] = 'D';
	}
}

void	finish_door(t_world *world, int i)
{
	t_vec2s					pos;
	t_door_anim_instance	*door;

	door = &world->active_doors[i];
	pos = door->pos;
	update_grid_char(world, pos, world->map->grid[pos.y][pos.x],
		door->type == DOOR_ANIM_OPENING);
	world->door_grid[pos.y * world->map->size.x + pos.x] = -1;
	door->active = false;
	door->state.frame = 0;
	door->state.timer_us = 0;
	door->state.playing = 0;
}
