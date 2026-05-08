/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:44:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 19:52:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"

static void	handle_enemy_death(t_world *world, t_entity *ent)
{
	ent->health = 0;
	set_state(ent, ENTITY_STATE_DIE, world->monster_die);
	ent->lifetime_us = ENTITY_DEATH_LIFETIME_US;
	drop_loot(world, ent->pos);
}

static bool	check_hit_entity(t_world *world, t_entity *ent, t_entity *proj,
		float r2)
{
	float	dist2;

	if (!ent->active || ent->type != ENTITY_ENEMY_GUARD
		|| ent->state == ENTITY_STATE_DIE)
		return (false);
	dist2 = (ent->pos.x - proj->pos.x) * (ent->pos.x - proj->pos.x)
		+ (ent->pos.y - proj->pos.y) * (ent->pos.y - proj->pos.y);
	if (dist2 >= r2)
		return (false);
	ent->health -= PROJECTILE_DAMAGE;
	if (ent->health <= 0)
		handle_enemy_death(world, ent);
	return (true);
}

static bool	projectile_hit_enemy(t_world *world, t_entity *proj)
{
	size_t	i;
	float	r2;

	i = 0;
	r2 = PROJECTILE_RADIUS * PROJECTILE_RADIUS + 0.25f;
	while (i < world->entity_count)
	{
		if (check_hit_entity(world, &world->entities[i++], proj, r2))
			return (true);
	}
	return (false);
}

void	tick_projectile(t_world *world, t_entity *ent, float dt)
{
	t_vec2	probe;

	probe.x = ent->pos.x + ent->vel.x * dt;
	probe.y = ent->pos.y + ent->vel.y * dt;
	if (is_wall(world, (t_vec3){probe.x, probe.y, 0.0f}))
	{
		ent->active = false;
		return ;
	}
	ent->pos = probe;
	if (projectile_hit_enemy(world, ent))
		ent->active = false;
}
