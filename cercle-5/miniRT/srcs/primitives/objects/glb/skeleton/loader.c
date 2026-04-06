/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:21:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:50:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

void	load_ibms(t_json_value *json, char *bin, int acc_idx, t_mat4 *dst);

static void	link_glb_parents(t_mesh *mesh, t_json_value *joints,
				t_json_value *nodes, size_t *node_map)
{
	t_json_value	*children;
	size_t			v[3];

	v[0] = 0;
	while (v[0] < joints->u.array.count)
	{
		t_index	rs;

		rs = json_as_t_index(json_at(joints, v[0]));
		if (rs.error)
		{
			v[0]++;
			continue ;
		}
		v[1] = rs.i;
		children = json_get(json_at(nodes, v[1]), "children");
		if (children)
		{
			v[2] = 0;
			while (v[2] < children->u.array.count)
			{
				t_index	rs2;

				rs2 = json_as_t_index(json_at(children, v[2]));
				if (!rs2.error && rs2.i != 0
					&& v[2] < PARSER_BUF_SIZE
					&& node_map[rs2.i] != 0)
					mesh->skeleton[node_map[rs2.i]].parent = init_index(v[0], false);
				v[2]++;
			}
		}
		v[0]++;
	}
}

static void	init_bone_data(t_mesh *mesh, t_json_value *joints,
				t_json_value *nodes, size_t *node_map)
{
	size_t	v[2];
	t_bone	*b;

	v[0] = 0;
	while (v[0] < mesh->bone_count)
	{
		t_index	rs;

		rs = json_as_t_index(json_at(joints, v[0]));
		if (rs.error)
		{
			v[0]++;
			continue ;
		}
		v[1] = rs.i;
		node_map[v[1]] = v[0];
		b = &mesh->skeleton[v[0]];
		b->node_idx = v[1];
		b->parent = init_index(0, true);
		mesh->bone_matrices[v[0]] = mat4_identity();
		fill_bone_trs(b, json_at(nodes, v[1]));
		v[0]++;
	}
}

/**
 * Main GLB skeleton loader. Allocates memory and fills bone data from joints.
 */
static void	setup_skeleton(t_mesh *mesh, size_t joint_count, size_t extra_count)
{
	mesh->skeleton = malloc(sizeof(t_bone) * (joint_count + extra_count));
	mesh->bone_matrices = malloc(sizeof(t_mat4) * (joint_count + extra_count));
	mesh->bone_count = joint_count;
}

static void	load_skeleton_data(t_mesh *mesh, t_json_value *js[2])
{
	size_t	*node_map;
	size_t	i;

	node_map = malloc(sizeof(*node_map) * PARSER_BUF_SIZE);
	i = 0;
	while (i < PARSER_BUF_SIZE)
	{
		node_map[i] = 0;
		i++;
	}
	init_bone_data(mesh, js[0], js[1], node_map);
	link_glb_parents(mesh, js[0], js[1], node_map);
	free(node_map);
}

void	glb_load_skeleton(t_mesh *mesh, t_json_value *json, char *bin,
			size_t extra_count)
{
	t_json_value	*skin;
	t_json_value	*js[2];
	t_mat4			*ibms;
	t_index			idx;
	size_t			i;

	skin = json_at(json_get(json, "skins"), 0);
	js[0] = json_get(skin, "joints");
	js[1] = json_get(json, "nodes");
	if (!skin || !js[0] || !js[1])
		return ;
	ft_print_debug("GLB: Skeleton: %zu joints, %zu extra nodes\n",
		js[0]->u.array.count, extra_count);
	setup_skeleton(mesh, js[0]->u.array.count, extra_count);
	ibms = malloc(sizeof(t_mat4) * mesh->bone_count);
	if (!ibms)
		return ;
	idx = json_get_size_t(skin, "inverseBindMatrices");
	load_ibms(json, bin, idx.i, ibms);
	load_skeleton_data(mesh, js);
	i = 0;
	while (i < mesh->bone_count)
	{
		mesh->skeleton[i].inv_bind_pose = ibms[i];
		i++;
	}
	free(ibms);
}
