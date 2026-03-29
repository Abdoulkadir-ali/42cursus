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
	int		bone_id;
	int		offset;
	int		count;
	float	w;
	t_mat4	blended;

	if (!sm->bone_matrices || sm->vertex_count == 0 || !sm->base_vertices)
		return ;
	if (!sm->skeleton_dirty)
		return ;
	i = -1;
	while (++i < sm->vertex_count)
	{
		v = sm->base_vertices[i];
		v.w = 1.0;
		ft_memset(&blended, 0, sizeof(t_mat4));
		offset = sm->weight_offsets[i];
		count = sm->weight_counts[i];
		b = -1;
		while (++b < count)
		{
			w = sm->weights[offset + b];
			if (w > 1e-6f)
			{
				bone_id = sm->bone_ids[offset + b];
				if (bone_id < sm->bone_count)
					blended = mat4_add(blended,
							mat4_scale_inplace(sm->bone_matrices[bone_id], w));
			}
		}
		sm->vertices[i] = mat4_mul_vec3(blended, v);
	}
	sm->skeleton_dirty = false;
}
