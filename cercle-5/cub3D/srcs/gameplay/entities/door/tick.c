/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 09:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/05 21:49:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "gameplay.h"

static void	step_door_frames(t_world *world, int i, int dur, t_anim_clip *clip)
{
	t_door_anim_instance	*door;
	float					progress;

	door = &world->active_doors[i];
	while (door->state.timer_us >= dur)
	{
		door->state.timer_us -= dur;
		door->state.frame++;
		if (door->state.frame >= clip->frame_count)
		{
			finish_door(world, i);
			return ;
		}
	}
	progress = (float)door->state.frame / (float)clip->frame_count;
	if (door->type == DOOR_ANIM_CLOSING)
		progress = 1.0f - progress;
	if (progress < 0.0f)
		progress = 0.0f;
	if (progress > 1.0f)
		progress = 1.0f;
	door->open_amount = progress;
}

void	tick_door(t_world *world, int i, int elapsed_us)
{
	t_anim_clip	*clip;
	int			dur;

	if (world->active_doors[i].type == DOOR_ANIM_CLOSING)
		clip = world->door_close_clip;
	else
		clip = world->door_open_clip;
	if (!clip || clip->frame_count == 0)
	{
		world->door_grid[world->active_doors[i].pos.y * world->map->size.x
			+ world->active_doors[i].pos.x] = -1;
		world->active_doors[i].active = false;
		return ;
	}
	dur = clip->frame_duration_us;
	if (dur <= 0)
		dur = 1000000 / 60;
	world->active_doors[i].state.timer_us += elapsed_us;
	step_door_frames(world, i, dur, clip);
}
