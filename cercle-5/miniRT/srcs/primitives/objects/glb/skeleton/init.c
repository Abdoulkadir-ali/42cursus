/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 03:19:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:19:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

void	init_bone_data(t_mesh *mesh, t_json_value *joints,
				t_json_value *nodes, size_t *node_map)
{
	size_t	i;
	t_bone	*b;
	t_index	rs;

	i = 0;
	while (i < mesh->bone_count)
	{
		rs = json_as_t_index(json_at(joints, i));
		if (!rs.error)
		{
			node_map[rs.i] = i;
			b = &mesh->skeleton[i];
			b->node_idx = rs.i;
			b->parent = init_index(0, true);
			mesh->bone_matrices[i] = mat4_identity();
			fill_bone_trs(b, json_at(nodes, rs.i));
		}
		i++;
	}
}

void	set_ibms(t_mesh *mesh, t_mat4 *ibms)
{
	size_t	i;

	i = 0;
	while (i < mesh->bone_count)
	{
		mesh->skeleton[i].inv_bind_pose = ibms[i];
		i++;
	}
}

void	setup_skeleton(t_mesh *mesh, size_t joint_count, size_t extra_count)
{
	mesh->skeleton = malloc(sizeof(t_bone) * (joint_count + extra_count));
	mesh->bone_matrices = malloc(sizeof(t_mat4) * (joint_count + extra_count));
	mesh->bone_count = joint_count;
}
