/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 23:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 22:27:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "pathfinder.h"

static void	find_path(t_world *world, t_entity *ent, t_vec2 *t, float *s)
{
	t_pathfinder_params	p;

	p = (t_pathfinder_params){world->map, ent->pos, *t, true, t};
	if (!pf_get_next_step(world->map, p))
		*s = 0;
}

static void	set_chase_state(t_world *world, t_entity *ent, float d, float s)
{
	if (s > 0 && d > 1.0f)
		set_state(ent, ENTITY_STATE_WALK, world->monster_walk);
	else if (s <= 0)
		set_state(ent, ENTITY_STATE_IDLE, world->monster_idle);
}

void	handle_chase(t_world *world, t_entity *ent, t_vec2 *t, float *s)
{
	t_vec2	p;
	float	d;

	p = (t_vec2){world->player.render_pos.x, world->player.render_pos.y};
	d = sqrtf(powf(p.x - ent->pos.x, 2) + powf(p.y - ent->pos.y, 2));
	if (d < 1.0f && check_los(world, ent->pos, p))
	{
		handle_attack(world, ent);
		return ;
	}
	*t = ent->last_seen_pos;
	*s = 1.6f;
	if (!check_los(world, ent->pos, *t))
		find_path(world, ent, t, s);
	set_chase_state(world, ent, d, *s);
}
