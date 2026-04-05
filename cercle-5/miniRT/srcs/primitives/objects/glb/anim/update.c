/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:33:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 16:36:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	apply_anim_channel(t_bone *bone, t_anim_channel *chan,
				t_anim_sampler *s, float time)
{
	float	res[4];

	res[0] = 0.0f;
	res[1] = 0.0f;
	res[2] = 0.0f;
	res[3] = 1.0f;

	if (chan->path == PATH_TRANSLATION)
	{
		sample_channel(s, time, res, 3);
		bone->trs.pos = vec3(res[0], res[1], res[2]);
	}
	else if (chan->path == PATH_ROTATION)
	{
		sample_channel(s, time, res, 4);
		bone->r_quat = (t_vec4){res[0], res[1], res[2], res[3]};
	}
	else if (chan->path == PATH_SCALE)
	{
		sample_channel(s, time, res, 3);
		bone->trs.scale = vec3(res[0], res[1], res[2]);
	}
}

static void	update_bone_recursive(t_mesh *mesh, int bone_idx, t_mat4 parent_mat)
{
	t_bone	*bone;
	double	s[3];
	size_t	i;

	bone = &mesh->skeleton[bone_idx];
	s[0] = bone->trs.scale.x;
	s[1] = bone->trs.scale.y;
	s[2] = bone->trs.scale.z;
	bone->local_transform = make_transform(bone->trs.pos, bone->r_quat, s);
	bone->global_transform = mat4_mul(bone->local_transform, parent_mat);
	mesh->bone_matrices[bone_idx] = mat4_mul(bone->inv_bind_pose,
			bone->global_transform);
	i = 0;
	while (i < mesh->bone_count)
	{
		if (!mesh->skeleton[i].parent.error
				&& mesh->skeleton[i].parent.i == (size_t)bone_idx)
			update_bone_recursive(mesh, i, bone->global_transform);
		i++;
	}
}

static void	apply_animation(t_mesh *mesh, t_animation *clip)
{
	size_t	i;
	size_t	bone_idx;

	i = 0;
	while (i < clip->channel_count)
	{
		bone_idx = 0;
		while (bone_idx < mesh->bone_count)
		{
			if (mesh->skeleton[bone_idx].node_idx
				== clip->channels[i].node_idx)
				apply_anim_channel(&mesh->skeleton[bone_idx],
					&clip->channels[i],
					&clip->samplers[clip->channels[i].sampler_idx],
					clip->current_time);
			bone_idx++;
		}
		i++;
	}
}

/**
 * Main animation update loop for GLB meshes. Advances clip time, updates bones,
 * and reapplies skinning/scene transforms.
 */
void	glb_update_mesh_anim(t_mesh *mesh, t_scene *scene, double dt)
{
	t_animation	*clip;
	size_t		i;

	if (!mesh->skeleton || scene->clip_count <= 0)
		return ;
	clip = &scene->clips[0];
	clip->current_time += dt;
	if (clip->current_time > clip->max_time)
		clip->current_time = fmod(clip->current_time, clip->max_time);
	apply_animation(mesh, clip);
	i = 0;
	while (i < mesh->bone_count)
	{
		if (mesh->skeleton[i].parent.error)
			update_bone_recursive(mesh, i, mat4_identity());
		i++;
	}
	glb_skin_mesh(mesh);
	glb_reapply_scene_transform(mesh);
}
