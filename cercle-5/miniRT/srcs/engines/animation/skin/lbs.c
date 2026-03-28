/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lbs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 09:35:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animations.h"

/**
 * Calculates the forward kinematics for the skeleton.
 * Correct row-vector order: ChildGlobal = ChildLocal * ParentGlobal.
 */
void	update_skeleton_hierarchy(t_skinned_mesh *sm)
{
	int		i;
	t_bone	*bone;

	i = 0;
	while (i < sm->bone_count)
	{
		bone = &sm->skeleton[i];
		if (bone->parent == -1)
			bone->global_transform = bone->local_transform;
		else
			bone->global_transform = mat4_mul(bone->local_transform,
											 sm->skeleton[bone->parent].global_transform);		
		sm->bone_matrices[i] = mat4_mul(bone->inv_bind_pose, bone->global_transform);
		i++;
	}
}

/**
 * Performs Linear Blend Skinning (LBS).
 * Now supports an arbitrary number of bone influences per vertex (flexible).
 */
void	update_skinned_mesh(t_skinned_mesh *sm)
{
	int		i;
	int		b;
	t_vec3	v;
	t_vec3	res;
	int		bone_id;
	int		offset;
	int		count;
	float	w;

	if (!sm->bone_matrices || sm->vertex_count == 0 || !sm->base_vertices)
		return ;
	i = 0;
	while (i < sm->vertex_count)
	{
		v = sm->base_vertices[i];
		v.w = 1.0;
		res = vec3(0, 0, 0);
		offset = sm->weight_offsets[i];
		count = sm->weight_counts[i];
		b = 0;
		while (b < count)
		{
			w = sm->weights[offset + b];
			if (w > 0.0f)
			{
				bone_id = sm->bone_ids[offset + b];
				res = vec3_add(res, vec3_scale(mat4_mul_vec3(sm->bone_matrices[bone_id], v), w));
			}
			b++;
		}
		sm->vertices[i] = res;
		i++;
	}
}
