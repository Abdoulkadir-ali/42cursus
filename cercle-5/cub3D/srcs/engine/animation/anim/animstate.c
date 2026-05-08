/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animstate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/26 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static const char	*get_clip_name(t_anim *wa, t_anim_clip *clip)
{
	if (clip == wa->clips.idle)
		return ("IDLE");
	if (clip == wa->clips.walking)
		return ("WALK");
	if (clip == wa->clips.shooting)
		return ("SHOOT");
	if (clip == wa->clips.reload)
		return ("RELOAD");
	if (clip == wa->clips.sprint)
		return ("SPRINT");
	return ("UNKNOWN");
}

t_anim_clip	*anim_get_active_clip(t_anim *wa)
{
	if (!wa)
		return (NULL);
	if (wa->reloading)
		return (wa->clips.reload);
	if (wa->firing)
		return (wa->clips.shooting);
	if (wa->moving && wa->sprinting && wa->clips.sprint
		&& wa->clips.sprint->frame_count > 0)
		return (wa->clips.sprint);
	if (wa->moving)
		return (wa->clips.walking);
	return (wa->clips.idle);
}

void	anim_set_active_clip(t_anim *wa, t_anim_clip *clip,
	int delay, int loop)
{
	const char		*name;

	if (!wa || !clip || clip->frame_count <= 0)
		return ;
	name = get_clip_name(wa, clip);
	wa->active_clip = clip;
	wa->state.frame = 0;
	wa->state.frame_count = clip->frame_count;
	wa->state.ticks = 0;
	wa->state.tick_delay = delay;
	wa->state.timer_us = 0;
	wa->state.loop = loop;
	wa->state.playing = 1;
	ft_print_debug("weapon action = %s\n", name);
}
