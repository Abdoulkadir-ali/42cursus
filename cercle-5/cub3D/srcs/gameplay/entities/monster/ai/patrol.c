/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patrol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 23:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 22:27:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

static void	pick_target(t_world *world, t_entity *ent)
{
	ent->target_pos.x = (float)(rand() % (world->map->size.x - 2)) + 1.5f;
	ent->target_pos.y = (float)(rand() % (world->map->size.y - 2)) + 1.5f;
	if (world->map->grid[(int)ent->target_pos.y][(int)ent->target_pos.x] == '0')
		set_state(ent, ENTITY_STATE_WALK, world->monster_walk);
	ent->idle_timer = 2.0f + (float)(rand() % 400) / 100.0f;
}

static void	patrol_walking(t_world *world, t_entity *ent)
{
	float	d;

	d = sqrtf(powf(ent->target_pos.x - ent->pos.x, 2)
			+ powf(ent->target_pos.y - ent->pos.y, 2));
	if (d < 0.2f)
	{
		set_state(ent, ENTITY_STATE_IDLE, world->monster_idle);
		ent->idle_timer = 2.0f + (float)(rand() % 400) / 100.0f;
	}
}

static void	patrol_idle(t_world *world, t_entity *ent, float dt)
{
	set_state(ent, ENTITY_STATE_IDLE, world->monster_idle);
	ent->idle_timer -= dt;
	if (ent->idle_timer <= 0)
		pick_target(world, ent);
}

void	handle_patrol(t_world *world, t_entity *ent, float dt)
{
	if (ent->state == ENTITY_STATE_WALK)
		patrol_walking(world, ent);
	else
		patrol_idle(world, ent, dt);
}
