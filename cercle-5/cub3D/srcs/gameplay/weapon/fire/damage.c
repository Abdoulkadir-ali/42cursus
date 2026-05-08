/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:31:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 10:17:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"

void	handle_enemy_hit(t_world *world, t_entity *ent)
{
	ent->health -= 40;
	if (ent->health <= 0)
	{
		ent->health = 0;
		set_state(ent, ENTITY_STATE_DIE, world->monster_die);
		ent->lifetime_us = ENTITY_DEATH_LIFETIME_US;
		drop_loot(world, ent->pos);
	}
	add_debug_sphere(world, (t_vec3){ent->pos.x, ent->pos.y, 0.5f}, 0.2f,
		(t_dbg_style){(t_vec3){255, 0, 0}, 500});
}

void	check_entity_damage(t_world *world, t_vec2 ray, float dist)
{
	size_t		i;
	t_entity	*ent;
	t_vec2		to_ent;
	float		ent_dist;
	float		dot;

	i = 0;
	while (i < world->entity_count)
	{
		ent = &world->entities[i];
		if (ent->active && ent->type == ENTITY_ENEMY_GUARD
			&& ent->state != ENTITY_STATE_DIE)
		{
			to_ent.x = ent->pos.x - world->player.render_pos.x;
			to_ent.y = ent->pos.y - world->player.render_pos.y;
			ent_dist = sqrtf(to_ent.x * to_ent.x + to_ent.y * to_ent.y);
			dot = (to_ent.x * ray.x + to_ent.y * ray.y) / ent_dist;
			if (ent_dist < dist + 0.5f && dot > 0.99f)
			{
				handle_enemy_hit(world, ent);
				break ;
			}
		}
		i++;
	}
}
