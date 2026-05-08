/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:38:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 19:49:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

static t_vec2i	calculate_axis(t_vec2 d)
{
	t_vec2i	a;

	a.x = 0;
	a.y = 0;
	if (fabsf(d.x) >= fabsf(d.y))
	{
		if (d.x > 0)
			a.x = 1;
		else
			a.x = -1;
	}
	else
	{
		if (d.y > 0)
			a.y = 1;
		else
			a.y = -1;
	}
	return (a);
}

static bool	pick_dir(t_world *world, t_vec2i pos, t_vec2i *dir)
{
	t_vec2i	a;
	t_vec2i	n;

	a = calculate_axis((t_vec2){world->player.actor.dir.x,
			world->player.actor.dir.y});
	n.x = pos.x + a.x;
	n.y = pos.y + a.y;
	if (n.x >= 0 && n.y >= 0 && (size_t)n.x < world->map->size.x
		&& (size_t)n.y < world->map->size.y
		&& world->map->grid[n.y][n.x] == '0')
	{
		*dir = a;
		return (true);
	}
	return (false);
}

static bool	find_available_slot(t_world *world, size_t *out)
{
	size_t	i;

	i = 0;
	while (i < MAX_PUSH_WALLS)
	{
		if (!world->push_walls[i].active)
		{
			*out = i;
			return (true);
		}
		i++;
	}
	return (false);
}

static void	init_push_wall(t_world *world, size_t slot, t_vec2s pos,
		t_vec2i dir)
{
	world->push_walls[slot].s = pos;
	world->push_walls[slot].d = dir;
	world->push_walls[slot].offset = 0.0f;
	world->push_walls[slot].active = true;
}

bool	try_interact_push(t_world *world)
{
	t_vec2i	pos;
	t_vec2i	dir;
	size_t	slot;
	t_actor	a;

	a = world->player.actor;
	pos.x = (int)(a.pos.x + a.dir.x);
	pos.y = (int)(a.pos.y + a.dir.y);
	if (pos.x < 0 || pos.y < 0 || (size_t)pos.x >= world->map->size.x
		|| (size_t)pos.y >= world->map->size.y
		|| world->map->grid[pos.y][pos.x] != 's')
		return (false);
	if (!pick_dir(world, pos, &dir))
		return (false);
	if (!find_available_slot(world, &slot))
		return (false);
	init_push_wall(world, slot, (t_vec2s){(size_t)pos.x, (size_t)pos.y}, dir);
	return (true);
}
