/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 23:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 23:50:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

static void	get_patrol_move(t_entity *ent, t_vec2 *target, float *speed)
{
	if (ent->state == ENTITY_STATE_WALK)
	{
		*target = ent->target_pos;
		*speed = 0.8f;
	}
}

static void	resolve_move(t_world *world, t_entity *ent, float dt)
{
	t_vec2	p;
	t_vec2	t;
	float	s;

	p.x = world->player.render_pos.x;
	p.y = world->player.render_pos.y;
	update_aggro(world, ent, p, dt);
	t = ent->pos;
	s = 0;
	if (ent->aggro_timer > 0)
		handle_chase(world, ent, &t, &s);
	else
	{
		handle_patrol(world, ent, dt);
		get_patrol_move(ent, &t, &s);
	}
	apply_move(world, ent, t, s);
}

void	tick_monster(t_world *world, t_entity *ent, float dt)
{
	if (ent->state == ENTITY_STATE_DIE)
		return ;
	resolve_move(world, ent, dt);
	if (ent->shoot_cooldown > 0)
		ent->shoot_cooldown -= dt;
}
