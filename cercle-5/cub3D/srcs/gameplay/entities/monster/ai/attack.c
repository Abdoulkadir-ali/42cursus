/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 23:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 22:27:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

void	handle_attack(t_world *world, t_entity *ent)
{
	set_state(ent, ENTITY_STATE_ATTACK, world->monster_attack);
	if (ent->shoot_cooldown <= 0 && ent->anim.frame >= 40
		&& ent->anim.frame <= 45)
	{
		rotate_player(&world->player.actor, 0.0f);
		ent->shoot_cooldown = 1.5f;
	}
}
