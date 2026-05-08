/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 22:58:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 22:23:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static t_anim_clip	*get_motion_clip(t_anim *wa)
{
	if (wa->moving && wa->sprinting && wa->clips.sprint
		&& wa->clips.sprint->frame_count > 0)
		return (wa->clips.sprint);
	if (wa->moving)
		return (wa->clips.walking);
	return (wa->clips.idle);
}

static void	handle_inputs(t_anim *wa, t_anim_params p)
{
	t_anim_clip	*desired;

	if (p.reload && wa->weapon_type != WEAPON_NONE
		&& !wa->reloading && !wa->firing)
	{
		wa->reloading = 1;
		anim_set_active_clip(wa, wa->clips.reload, 5, 0);
	}
	else if (p.fire && wa->weapon_type != WEAPON_NONE && !wa->reloading)
	{
		wa->firing = 1;
		anim_set_active_clip(wa, wa->clips.shooting, 5, 0);
	}
	else if (!wa->firing && !wa->reloading)
	{
		desired = get_motion_clip(wa);
		if (wa->active_clip != desired)
			anim_set_active_clip(wa, desired, 8, 1);
	}
}

static void	update_timer(t_anim *wa, t_anim_params p, int elapsed_us)
{
	int		trig;
	float	scale;
	int		dur;

	trig = (wa->firing || wa->reloading);
	scale = 1.0f;
	if (trig)
		scale = p.attack_scale;
	else if (wa->moving)
		scale = p.move_scale;
	dur = 1000000 / 60;
	if (wa->active_clip && wa->active_clip->frame_duration_us > 0)
		dur = wa->active_clip->frame_duration_us;
	wa->state.timer_us += (int)((float)elapsed_us * scale);
	while (wa->state.timer_us >= dur)
	{
		wa->state.timer_us -= dur;
		wa->state.frame++;
	}
}

void	tick_weapon_anim(t_anim *wa, t_anim_params p, int elapsed_us)
{
	if (!wa)
		return ;
	wa->moving = p.move;
	wa->sprinting = p.sprint;
	if (p.move_scale <= 0)
		p.move_scale = 1.0f;
	if (p.attack_scale <= 0)
		p.attack_scale = 1.0f;
	wa->bob_phase += p.move * 0.18f * p.move_scale;
	handle_inputs(wa, p);
	if (!wa->state.playing)
		return ;
	update_timer(wa, p, elapsed_us);
	if (!wa->state.loop && wa->state.frame >= wa->state.frame_count)
	{
		wa->state.frame = 0;
		wa->firing = 0;
		wa->reloading = 0;
		anim_set_active_clip(wa, get_motion_clip(wa), 8, 1);
	}
	else if (wa->state.frame_count > 0)
		wa->state.frame %= wa->state.frame_count;
}
