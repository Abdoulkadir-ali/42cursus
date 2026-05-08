/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:41:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 09:41:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

static void	advance_frame(t_world *world, t_entity *ent)
{
	ent->anim.frame++;
	if (ent->anim.frame < ent->clip->frame_count)
		return ;
	if (ent->state == ENTITY_STATE_DIE)
		ent->anim.frame = ent->clip->frame_count - 1;
	else if (ent->state == ENTITY_STATE_ATTACK)
		set_state(ent, ENTITY_STATE_IDLE, world->monster_idle);
	else
		ent->anim.frame = 0;
}

void	tick_anim_ent(t_world *world, t_entity *ent, int elapsed_us)
{
	int		frame_dur;
	float	scale;

	if (!ent->clip)
		return ;
	scale = ent->anim_speed_scale;
	if (scale <= 0)
		scale = 1.0f;
	ent->anim.timer_us += (int)((float)elapsed_us * scale);
	frame_dur = ent->clip->frame_duration_us;
	if (frame_dur <= 0)
		frame_dur = 100000;
	while (ent->anim.timer_us >= frame_dur)
	{
		ent->anim.timer_us -= frame_dur;
		advance_frame(world, ent);
	}
}
