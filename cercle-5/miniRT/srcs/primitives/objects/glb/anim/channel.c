/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:32:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 12:33:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	interpolate_vec3(float *res, float t, float *a, float *b)
{
	vec3_mix(res, a, b, t);
}

static void	interpolate_quat(float *res, float t, float *a, float *b)
{
	quat_slerp(res, a, b, t);
}

static void	apply_interpolation(t_anim_sampler *s, float t, float *res,
				int stride)
{
	size_t	idx;

	idx = 0;
	while (idx < s->count - 1 && t > s->inputs[idx + 1])
		idx++;
	t = (t - s->inputs[idx]) / (s->inputs[idx + 1] - s->inputs[idx]);
	if (stride == 4)
		interpolate_quat(res, t, &s->outputs[idx * 4],
			&s->outputs[(idx + 1) * 4]);
	else
		interpolate_vec3(res, t, &s->outputs[idx * stride],
			&s->outputs[(idx + 1) * stride]);
}

/**
 * Samples an animation sampler at a specific time, with interpolation.
 */
void	sample_channel(t_anim_sampler *s, float time, float *res, int stride)
{
	int		i;

	if (s->count == 0 || !s->inputs || !s->outputs)
		return ;
	if (time <= s->inputs[0])
	{
		i = 0;
		while (i < stride)
		{
			res[i] = s->outputs[i];
			i++;
		}
		return ;
	}
	if (time >= s->inputs[s->count - 1])
	{
		i = 0;
		while (i < stride)
		{
			res[i] = s->outputs[(s->count - 1) * stride + i];
			i++;
		}
		return ;
	}
	apply_interpolation(s, time, res, stride);
}
