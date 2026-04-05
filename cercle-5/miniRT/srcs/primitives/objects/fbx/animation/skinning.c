/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skinning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 12:25:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

/**
 * Performs Linear Blend Skinning (LBS).
 * Updates the base mesh vertices based on bone matrices and weights.
 *
 * @param mesh The skinned mesh to update.
 */
void	update_skinned_mesh(t_skinned_mesh *mesh)
{
	size_t	i;
	int		b;
	t_vec3	v;
	t_vec3	res;

	if (!mesh->skeleton || mesh->bone_count == 0 || !mesh->base.vertices)
		return ;
	i = 0;
	while (i < mesh->vertex_count)
	{
		v = mesh->base_vertices[i];
		res = vec3(0, 0, 0);
		b = -1;
		while (++b < 4)
		{
			if (mesh->weights[i].weights[b] <= 0.0f)
				continue ;
			res = vec3_add(res, vec3_scale(mat4_mul_vec3(
							mesh->bone_matrices[
							mesh->weights[i].bone_indices[b]], v),
						mesh->weights[i].weights[b]));
		}
		mesh->base.vertices[i].pos = res;
		i++;
	}
}

/**

	* Calculates the forward kinematics for the skeleton.
 *
 * @param mesh The mesh whose skeleton should be updated.
 */
void	update_skeleton_hierarchy(t_skinned_mesh *mesh)
{
	size_t	i;
	t_bone	*bone;

	i = 0;
	while (i < mesh->bone_count)
	{
		bone = &mesh->skeleton[i];
		if (!bone->parent.error)
			mesh->bone_matrices[i] = mat4_mul(mesh->bone_matrices[bone->parent.i],
					bone->local_transform);
		else
			mesh->bone_matrices[i] = bone->local_transform;
		i++;
	}
}
