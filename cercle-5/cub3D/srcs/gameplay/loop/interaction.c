/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:00:39 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/05 21:49:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

static int	find_active_door_index(t_world *world, t_vec2s pos)
{
	int	i;

	i = 0;
	while (i < MAX_ACTIVE_DOORS)
	{
		if (world->active_doors[i].active
			&& world->active_doors[i].pos.x == pos.x
			&& world->active_doors[i].pos.y == pos.y)
			return (i);
		i++;
	}
	return (-1);
}

static void	init_door_anim(t_world *world, int i, t_vec2s c, int type)
{
	world->active_doors[i].pos = c;
	world->active_doors[i].active = true;
	world->door_grid[c.y * world->map->size.x + c.x] = i;
	world->active_doors[i].type = type;
	world->active_doors[i].state.frame = 0;
	world->active_doors[i].state.timer_us = 0;
	world->active_doors[i].state.playing = 1;
	if (type == DOOR_ANIM_OPENING)
		world->active_doors[i].open_amount = 0.0f;
	else
		world->active_doors[i].open_amount = 1.0f;
}

static void	activate_door(t_world *world, t_vec2s c, int type)
{
	int	i;

	i = 0;
	while (i < MAX_ACTIVE_DOORS)
	{
		if (!world->active_doors[i].active)
		{
			init_door_anim(world, i, c, type);
			break ;
		}
		i++;
	}
}

void	try_interact_door(t_world *world)
{
	t_vec3	pos;
	t_vec2	dir;
	t_vec2s	c;

	pos = world->player.actor.pos;
	dir.x = world->player.actor.dir.x;
	dir.y = world->player.actor.dir.y;
	if (pos.x + dir.x < 0.0f || pos.y + dir.y < 0.0f)
		return ;
	c.x = (size_t)(pos.x + dir.x);
	c.y = (size_t)(pos.y + dir.y);
	if (c.x >= world->map->size.x || c.y >= world->map->size.y)
		return ;
	if (find_active_door_index(world, c) != -1)
		return ;
	if (world->map->grid[c.y][c.x] == '2'
		|| world->map->grid[c.y][c.x] == 'd'
		|| world->map->grid[c.y][c.x] == 'D')
		activate_door(world, c, DOOR_ANIM_OPENING);
	else if (world->map->grid[c.y][c.x] == 'O'
		|| world->map->grid[c.y][c.x] == 'e'
		|| world->map->grid[c.y][c.x] == 'E')
		activate_door(world, c, DOOR_ANIM_CLOSING);
}
