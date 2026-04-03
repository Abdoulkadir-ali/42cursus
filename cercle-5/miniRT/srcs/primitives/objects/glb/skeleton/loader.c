/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:21:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:09:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	load_ibms(t_json_value *json, char *bin, int acc_idx, t_mat4 *dst)
{
	t_accessor		acc;
	t_buffer_view	bv;
	float			*tmp;
	size_t	v[3];

	glb_parse_accessor(json, acc_idx, &acc);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	tmp = malloc(sizeof(float) * 16 * acc.count);
	if (!tmp)
		return ;
	glb_extract_data((t_extract){bin, &acc, &bv, tmp, sizeof(float) * 16,
		sizeof(float) * 16, sizeof(float) * 16, acc.count});
	v[0] = -1;
	while (++v[0] < acc.count)
	{
		v[1] = -1;
		while (++v[1] < 4)
		{
			v[2] = -1;
			while (++v[2] < 4)
				dst[v[0]].m[v[2]][v[1]] = tmp[v[0] * 16 + v[2] * 4 + v[1]];
		}
	}
	free(tmp);
}

static void	link_glb_parents(t_mesh *mesh, t_json_value *joints,
				t_json_value *nodes, size_t *node_map)
{
	t_json_value	*children;
	size_t	v[3];

	v[0] = -1;
	while (v[0] < joints->u.array.count)
	{
		v[1] = json_as_number(json_at(joints, v[0]));
		children = json_get(json_at(nodes, v[1]), "children");
		if (children)
		{
			v[2] = -1;
			while (++v[2] < children->u.array.count)
			{
				v[1] = json_as_number(json_at(children, v[2]));
				if (v[1] != (size_t)-1 && v[2] < PARSER_BUF_SIZE && node_map[v[1]] != (size_t)-1)
					mesh->skeleton[node_map[v[1]]].parent = v[0];
			}
		}
	}
}

static void	init_bone_data(t_mesh *mesh, t_json_value *joints,
				t_json_value *nodes, size_t *node_map)
{
	size_t	v[2];
	t_bone	*b;

	v[0] = -1;
	while (++v[0] < mesh->bone_count)
	{
		v[1] = json_as_number(json_at(joints, v[0]));
		node_map[v[1]] = v[0];
		b = &mesh->skeleton[v[0]];
		b->node_idx = v[1];
		b->parent = -1;
		mesh->bone_matrices[v[0]] = mat4_identity();
		fill_bone_trs(b, json_at(nodes, v[1]));
	}
}

/**
 * Main GLB skeleton loader. Allocates memory and fills bone data from joints.
 */
static void	alloc_skeleton(t_mesh *mesh, size_t joint_count, size_t extra_count)
{
	mesh->skeleton = malloc(sizeof(t_bone) * (joint_count + extra_count));
	mesh->bone_matrices = malloc(sizeof(t_mat4) * (joint_count + extra_count));
	mesh->bone_count = joint_count;
}

void	glb_load_skeleton(t_mesh *mesh, t_json_value *json, char *bin,
			size_t extra_count)
{
	t_json_value	*skin;
	t_json_value	*joints[2];
	t_mat4			*ibms;
	size_t			*node_map;
	size_t			i;

	skin = json_at(json_get(json, "skins"), 0);
	joints[0] = json_get(skin, "joints");
	joints[1] = json_get(json, "nodes");
	if (!skin || !joints[0] || !joints[1])
		return ;
	alloc_skeleton(mesh, joints[0]->u.array.count, extra_count);
	ibms = malloc(sizeof(t_mat4) * mesh->bone_count);
	load_ibms(json, bin, json_get_size_t(skin, "inverseBindMatrices", NULL), ibms);
	node_map = malloc(sizeof(size_t) * PARSER_BUF_SIZE);
	i = -1;
	while (++i < PARSER_BUF_SIZE)
		node_map[i] = -1;
	init_bone_data(mesh, joints[0], joints[1], node_map);
	i = -1;
	while (++i < mesh->bone_count)
		mesh->skeleton[i].inv_bind_pose = ibms[i];
	link_glb_parents(mesh, joints[0], joints[1], node_map);
	free(ibms);
	free(node_map);
}
