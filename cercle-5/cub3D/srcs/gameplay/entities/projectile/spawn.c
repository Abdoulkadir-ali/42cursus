/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:44:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 10:24:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "engine.h"

static bool	init_projectile_motion(t_entity *ent, t_vec2 pos, t_vec2 dir)
{
	float	mag;

	mag = sqrtf(dir.x * dir.x + dir.y * dir.y);
	if (mag < 0.00001f)
		return (false);
	ent->pos.x = pos.x + (dir.x / mag) * 0.4f;
	ent->pos.y = pos.y + (dir.y / mag) * 0.4f;
	ent->target_pos = ent->pos;
	ent->vel.x = (dir.x / mag) * PROJECTILE_SPEED;
	ent->vel.y = (dir.y / mag) * PROJECTILE_SPEED;
	return (true);
}

static void	init_projectile_stats(t_entity *ent, t_world *world)
{
	ent->type = ENTITY_PROJECTILE;
	ent->state = ENTITY_STATE_IDLE;
	ent->active = true;
	ent->health = 1;
	ent->lifetime_us = PROJECTILE_LIFETIME_US;
	ent->anim.frame = 0;
	ent->anim.timer_us = 0;
	ent->anim_speed_scale = 1.0f;
	ent->current_speed = PROJECTILE_SPEED;
	ent->shoot_cooldown = 0;
	ent->idle_timer = 0;
	ent->aggro_timer = 0;
	ent->clip = world->ammo_clip;
}

void	spawn_projectile(t_world *world, t_vec2 pos, t_vec2 dir)
{
	t_entity	*ent;

	if (!world || world->entity_count >= MAX_ENTITIES)
		return ;
	ent = &world->entities[world->entity_count];
	if (!init_projectile_motion(ent, pos, dir))
		return ;
	world->entity_count++;
	init_projectile_stats(ent, world);
}
