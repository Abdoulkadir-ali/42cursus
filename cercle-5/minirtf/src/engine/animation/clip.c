/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 03:20:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skeletal.h"

static t_keyframe	locate_keys(const t_anim_chan *ch, float t)
{
	t_keyframe	k;
	int			m;
	float		dt;

	k.lo = 0;
	k.hi = ch->n_keys - 1;
	k.alpha = 0.0f;
	if (t <= ch->times[0] || k.hi == 0)
		return (k.hi = k.lo, k);
	if (t >= ch->times[k.hi])
		return (k.lo = k.hi, k);
	while (k.hi - k.lo > 1)
	{
		m = (k.lo + k.hi) >> 1;
		if (ch->times[m] <= t)
			k.lo = m;
		else
			k.hi = m;
	}
	dt = ch->times[k.hi] - ch->times[k.lo];
	if (dt > 1e-9f)
		k.alpha = (t - ch->times[k.lo]) / dt;
	if (ch->interp == 1)
		k.alpha = 0.0f;
	return (k);
}

static t_vec3	lerp_vec3(const float *a, const float *b, float u)
{
	t_vec3	o;

	o.x = a[0] + u * (b[0] - a[0]);
	o.y = a[1] + u * (b[1] - a[1]);
	o.z = a[2] + u * (b[2] - a[2]);
	return (o);
}

static t_vec4	read_quat(const float *p)
{
	t_vec4	q;

	q.x = p[0];
	q.y = p[1];
	q.z = p[2];
	q.w = p[3];
	return (q);
}

static void	apply_chan(t_animator *a, t_anim_chan *ch, float t)
{
	t_keyframe	k;
	t_anim_node	*n;

	k = locate_keys(ch, t);
	n = &a->nodes[ch->target_node];
	if (ch->path == 0)
		n->t = lerp_vec3(&ch->values[k.lo * 3], &ch->values[k.hi * 3], k.alpha);
	else if (ch->path == 2)
		n->s = lerp_vec3(&ch->values[k.lo * 3], &ch->values[k.hi * 3], k.alpha);
	else if (ch->path == 1)
		n->r = skel_q_slerp(read_quat(&ch->values[k.lo * 4]),
				read_quat(&ch->values[k.hi * 4]), k.alpha);
}

void	skel_apply_clip(t_animator *a)
{
	t_anim_clip	*clip;
	t_anim_chan	*ch;
	float		t;
	int			c;

	if (a->active < 0 || a->active >= a->n_clips)
		return ;
	clip = &a->clips[a->active];
	t = a->time;
	if (clip->duration > 0.0f && a->loop)
		t = fmodf(t, clip->duration);
	t = ft_clampf(t, 0.0f, clip->duration);
	c = 0;
	while (c < clip->n_chans)
	{
		ch = &clip->chans[c];
		if (ch->n_keys > 0 && ch->target_node >= 0
			&& ch->target_node < a->n_nodes)
			apply_chan(a, ch, t);
		c++;
	}
}
