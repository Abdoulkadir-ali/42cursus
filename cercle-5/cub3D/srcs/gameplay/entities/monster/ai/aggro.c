/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 23:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 22:27:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

void	update_aggro(t_world *world, t_entity *ent, t_vec2 p_pos, float dt)
{
	float	dist;

	dist = sqrtf(powf(p_pos.x - ent->pos.x, 2)
			+ powf(p_pos.y - ent->pos.y, 2));
	if (check_los(world, ent->pos, p_pos) && dist < 8.0f)
	{
		ent->aggro_timer = 5.0f;
		ent->last_seen_pos = p_pos;
	}
	else if (ent->aggro_timer > 0)
		ent->aggro_timer -= dt;
}
