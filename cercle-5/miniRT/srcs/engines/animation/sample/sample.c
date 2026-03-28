/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 09:42:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animations.h"

void	anim_advance_time(t_skinned_mesh *sm, t_animation *clip, float dt)
{
	if (!clip)
		return;
	sm->anim_time += dt;
	if (sm->anim_time > clip->max_time && clip->max_time > 0.0f)
		sm->anim_time = fmod(sm->anim_time, clip->max_time);
}

int	anim_find_bracket(t_anim_sampler *s, float time, float *t_out)
{
	int	i;

	*t_out = 0.0f;
	if (s->count == 0) return (0);
	if (time <= s->inputs[0]) return (0);
	if (time >= s->inputs[s->count - 1]) return (s->count - 1);
	
	i = 0;
	while (i < s->count - 1)
	{
		if (time >= s->inputs[i] && time <= s->inputs[i + 1])
		{
			*t_out = (time - s->inputs[i]) / (s->inputs[i + 1] - s->inputs[i]);
			return (i);
		}
		i++;
	}
	return (0);
}
