/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 10:22:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

static void	spawn_map_entity(t_world *world, char c, t_vec2s pos)
{
	t_vec2	spawn_pos;

	spawn_pos.x = (float)pos.x + 0.5f;
	spawn_pos.y = (float)pos.y + 0.5f;
	if (c == 'G' || c == 'm')
		spawn_entity(world, ENTITY_ENEMY_GUARD, spawn_pos);
	else if (c == 'M' || c == 'p')
		spawn_entity(world, ENTITY_ITEM_MEDKIT, spawn_pos);
	else if (c == 'A')
		spawn_entity(world, ENTITY_ITEM_AMMO, spawn_pos);
	else if (c == 'P' || c == 's')
		spawn_entity(world, ENTITY_ITEM_SHIELD, spawn_pos);
}

void	init_entities(t_world *world)
{
	t_vec2s	pos;

	world->entity_count = 0;
	pos.y = 0;
	while (pos.y < world->map->size.y)
	{
		pos.x = 0;
		while (pos.x < world->map->size.x)
		{
			spawn_map_entity(world, world->map->grid[pos.y][pos.x], pos);
			pos.x++;
		}
		pos.y++;
	}
}
