/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 10:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include <stdlib.h>

static void	init_ent_stats(t_entity *ent)
{
	ent->state = ENTITY_STATE_IDLE;
	ent->active = true;
	ent->health = 100;
	ent->anim.frame = 0;
	ent->anim.timer_us = 0;
	ent->shoot_cooldown = 0;
	ent->idle_timer = (float)(rand() % 5);
	ent->current_speed = 0;
	ent->anim_speed_scale = 1.0f;
	ent->lifetime_us = 0;
}

static void	init_monster(t_world *world, t_entity *ent)
{
	ent->clip = world->enemy_guard_clip;
	if (world->monster_idle)
		ent->clip = world->monster_idle;
}

static void	init_item(t_world *world, t_entity *ent, t_entity_type type)
{
	if (type == ENTITY_ITEM_MEDKIT)
		ent->clip = world->medkit_clip;
	else if (type == ENTITY_ITEM_AMMO)
		ent->clip = world->ammo_clip;
	else if (type == ENTITY_ITEM_SHIELD)
		ent->clip = world->shield_clip;
	else
		ent->clip = NULL;
	ent->lifetime_us = ITEM_LIFETIME_US;
}

void	spawn_entity(t_world *world, t_entity_type type, t_vec2 pos)
{
	t_entity	*ent;

	if (world->entity_count >= MAX_ENTITIES)
		return ;
	ent = &world->entities[world->entity_count++];
	ent->pos = pos;
	ent->target_pos = pos;
	ent->type = type;
	init_ent_stats(ent);
	if (type == ENTITY_ENEMY_GUARD)
		init_monster(world, ent);
	else if (type == ENTITY_ITEM_MEDKIT || type == ENTITY_ITEM_AMMO
		|| type == ENTITY_ITEM_SHIELD)
		init_item(world, ent, type);
	else
		ent->clip = NULL;
}
