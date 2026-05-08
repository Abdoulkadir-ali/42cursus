/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 19:50:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

static void	tick_ent(t_world *world, t_entity *ent, float dt, int elapsed_us)
{
	if (ent->type == ENTITY_ENEMY_GUARD)
		tick_monster(world, ent, dt);
	else if (ent->type == ENTITY_PROJECTILE)
		tick_projectile(world, ent, dt);
	else
		tick_item(world, ent);
	tick_anim_ent(world, ent, elapsed_us);
}

static void	remove_entity(t_world *world, size_t idx)
{
	size_t	last;

	last = world->entity_count - 1;
	if (idx < last)
		world->entities[idx] = world->entities[last];
	world->entity_count--;
}

static void	cleanup_entities(t_world *world)
{
	size_t	i;

	i = 0;
	while (i < world->entity_count)
	{
		if (!world->entities[i].active)
			remove_entity(world, i);
		else
			i++;
	}
}

static void	update_lifetime(t_entity *ent, int elapsed_us)
{
	if (ent->lifetime_us <= 0)
		return ;
	ent->lifetime_us -= elapsed_us;
	if (ent->lifetime_us > 0)
		return ;
	if (ent->state == ENTITY_STATE_DIE || ent->type == ENTITY_ITEM_MEDKIT
		|| ent->type == ENTITY_ITEM_AMMO || ent->type == ENTITY_ITEM_SHIELD
		|| ent->type == ENTITY_PROJECTILE)
		ent->active = false;
}

void	tick_entities(t_world *world, int elapsed_us)
{
	float	dt;
	size_t	i;

	dt = (float)elapsed_us / 1000000.0f;
	i = 0;
	while (i < world->entity_count)
	{
		if (world->entities[i].active)
			tick_ent(world, &world->entities[i], dt, elapsed_us);
		update_lifetime(&world->entities[i++], elapsed_us);
	}
	cleanup_entities(world);
}
