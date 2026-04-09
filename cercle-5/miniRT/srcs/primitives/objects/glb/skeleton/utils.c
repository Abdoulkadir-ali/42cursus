/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 03:10:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:19:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

t_mat4	make_transform(t_vec3 t, t_vec4 r_quat, double scale[3])
{
	t_mat4	mt;
	t_mat4	mr;
	t_mat4	ms;

	mt = mat4_translation(t);
	mr = quat_to_mat4(r_quat);
	ms = mat4_scaling(vec3(scale[0], scale[1], scale[2]));
	return (mat4_mul(ms, mat4_mul(mr, mt)));
}

static t_index	search_parent(t_json_value *nodes, size_t node_idx)
{
	t_json_value	*node;
	t_json_value	*children;
	size_t			i;
	size_t			k;
	t_index			rs;

	i = 0;
	while (i < nodes->u.array.count)
	{
		node = json_at(nodes, i);
		children = json_get(node, "children");
		if (children && children->type == JSON_ARRAY)
		{
			k = 0;
			while (k < children->u.array.count)
			{
				rs = json_as_t_index(json_at(children, k));
				if (!rs.error && rs.i == node_idx)
					return (init_index(i, false));
				k++;
			}
		}
		i++;
	}
	return (init_index(0, true));
}

t_index	find_parent_node(t_json_value *json, size_t node_idx)
{
	t_json_value	*nodes;

	nodes = json_get(json, "nodes");
	if (!nodes || nodes->type != JSON_ARRAY)
		return (init_index(0, true));
	return (search_parent(nodes, node_idx));
}

void	link_glb_bone_children(t_mesh *mesh, t_index p_idx,
				t_json_value *node, size_t *node_map)
{
	t_json_value	*children;
	size_t			k;
	t_index			rs2;

	children = json_get(node, "children");
	if (!children)
		return ;
	k = 0;
	while (k < children->u.array.count)
	{
		rs2 = json_as_t_index(json_at(children, k));
		if (!rs2.error && rs2.i != 0
			&& k < PARSER_BUF_SIZE
			&& node_map[rs2.i] != 0)
			mesh->skeleton[node_map[rs2.i]].parent = p_idx;
		k++;
	}
}

void	link_glb_parents(t_mesh *mesh, t_json_value *joints,
				t_json_value *nodes, size_t *node_map)
{
	size_t	i;
	t_index	rs;

	i = 0;
	while (i < joints->u.array.count)
	{
		rs = json_as_t_index(json_at(joints, i));
		if (!rs.error)
			link_glb_bone_children(mesh, init_index(i, false),
				json_at(nodes, rs.i), node_map);
		i++;
	}
}
