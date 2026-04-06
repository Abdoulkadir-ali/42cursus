/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skinning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:29:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

static t_vec3	blend_vertex(t_skinned_mesh *mesh, size_t i, t_vec3 v)
{
	t_vec3	res;
	t_vec3	contrib;
	t_mat4	mat;
	size_t	b;

	res = vec3(0, 0, 0);
	b = 0;
	while (b < 4)
	{
		if (mesh->weights[i].weights[b] > 0.0f)
		{
			mat = mesh->bone_matrices[mesh->weights[i].bone_indices[b]];
			contrib = mat4_mul_vec3(mat, v);
			res = vec3_add(res, vec3_scale(contrib,
						mesh->weights[i].weights[b]));
		}
		b++;
	}
	return (res);
}

void	update_skinned_mesh(t_skinned_mesh *mesh)
{
	size_t	i;
	t_vec3	v;

	if (!mesh->skeleton || mesh->bone_count == 0 || !mesh->base.vertices)
		return ;
	i = 0;
	while (i < mesh->vertex_count)
	{
		v = mesh->base_vertices[i];
		mesh->base.vertices[i].pos = blend_vertex(mesh, i, v);
		i++;
	}
}

/**
 * @brief Calculates the forward kinematics for the skeleton.
 *
 * @param mesh The mesh whose skeleton should be updated.
 */
void	update_skeleton_hierarchy(t_skinned_mesh *mesh)
{
	t_mat4	parent;
	size_t	i;
	t_bone	*bone;

	i = 0;
	while (i < mesh->bone_count)
	{
		bone = &mesh->skeleton[i];
		if (!bone->parent.error)
		{
			parent = mesh->bone_matrices[bone->parent.i];
			mesh->bone_matrices[i] = mat4_mul(parent, bone->local_transform);
		}
		else
			mesh->bone_matrices[i] = bone->local_transform;
		i++;
	}
}
