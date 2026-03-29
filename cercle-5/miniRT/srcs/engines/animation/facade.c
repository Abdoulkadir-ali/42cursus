/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   facade.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 09:31:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animations.h"
#include "debug.h"

/*
** Animation engine pipeline entry point.
**
** Pipeline per skinned mesh per frame:
**   1. anim_advance_time        — advance + loop anim_time
**   2. per channel:
**      anim_find_bracket        — locate keyframe bracket [a,b] + blend t
**      anim_interpolate         — lerp/slerp keyframe values into t_vec3
**      set bone->trs            — pos / rot / scale per path
**   3. anim_apply_trs_to_bone   — write local_transform = T*R*S per bone
**   4. update_skeleton_hierarchy — forward kinematics  (bone_matrices[])
**   5. update_skinned_mesh       — LBS vertex blend    (vertices[])
*/

static t_bone	*find_bone_by_node(t_skinned_mesh *sm, int node_idx)
{
	int	i;

	i = 0;
	while (i < sm->bone_count)
	{
		if (sm->skeleton[i].node_idx == node_idx)
			return (&sm->skeleton[i]);
		i++;
	}
	return (NULL);
}

static void	apply_channel(t_skinned_mesh *sm, t_anim_channel *ch,
		t_anim_sampler *samplers)
{
	t_anim_sampler	*samp;
	t_bone			*bone;
	float			t;
	int				frame;
	t_vec3			val;

	samp = &samplers[ch->sampler_idx];
	bone = find_bone_by_node(sm, ch->node_idx);
	if (!bone)
		return ;
	frame = anim_find_bracket(samp, (float)sm->anim_time, &t);
	val = anim_interpolate(samp, frame, t, ch->path);
	if (ch->path == PATH_TRANSLATION)
		bone->trs.pos = val;
	else if (ch->path == PATH_ROTATION)
		bone->trs.rot = val;
	else if (ch->path == PATH_SCALE)
		bone->trs.scale = val;
}

static void	apply_clip_channels(t_skinned_mesh *sm, t_animation *clip)
{
	int	j;

	j = 0;
	while (j < clip->channel_count)
	{
		apply_channel(sm, &clip->channels[j], clip->samplers);
		j++;
	}
}

static void	apply_trs_to_skeleton(t_skinned_mesh *sm)
{
	int	k;

	k = 0;
	while (k < sm->bone_count)
	{
		anim_apply_trs_to_bone(&sm->skeleton[k],
			sm->skeleton[k].trs.pos,
			sm->skeleton[k].trs.rot,
			sm->skeleton[k].trs.scale);
		k++;
	}
}

static void	dbg_log_clip(t_skinned_mesh *sm, t_animation *clip)
{
	char	*cn;

	cn = clip->name;
	if (!cn)
		cn = "?";
	DBG_INFO_MSG(DBG_CH_ANIM,
		"update_animations: clip=%s t=%.3f\n", cn, sm->anim_time);
}

void	update_animations(t_scene *scene, double dt)
{
	size_t			i;
	t_skinned_mesh	*sm;
	t_animation		*clip;

	DBG_ENTER("update_animations");
	i = 0;
	while (i < scene->anim_count)
	{
		sm = &scene->animated[i++];
		if (sm->current_anim < 0
			|| (size_t)sm->current_anim >= scene->clip_count)
			continue ;
		clip = &scene->clips[sm->current_anim];
		dbg_log_clip(sm, clip);
		anim_advance_time(sm, clip, (float)dt);
		apply_clip_channels(sm, clip);
		apply_trs_to_skeleton(sm);
		update_skeleton_hierarchy(sm);
		update_skinned_mesh(sm);
	}
	DBG_LEAVE("update_animations");
}
