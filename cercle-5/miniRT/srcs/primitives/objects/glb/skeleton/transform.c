/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 10:46:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:40:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static t_index	find_parent_node(t_json_value *json, size_t node_idx)
{
	t_json_value	*nodes;
	t_json_value	*node;
	t_json_value	*children;
	size_t			i;
	size_t			k;

	nodes = json_get(json, "nodes");
	if (!nodes || nodes->type != JSON_ARRAY)
		return (init_index(0, true));
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
				t_index	rs;

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

t_mat4	glb_node_transform(t_json_value *node)
{
	t_json_value	*v;
	t_vec3			t;
	t_vec4			r;
	double			s[3];

	v = json_get(node, "matrix");
	if (v && v->type == JSON_ARRAY && v->u.array.count >= 16)
	{
		t_mat4 m;
		int j = 0;
		while (j < 16)
		{
			m.m[j % 4][j / 4] = json_as_number(json_at(v, j));
			j++;
		}
		return (m);
	}
	t = vec3(0, 0, 0);
	r = (t_vec4){0, 0, 0, 1};
	s[0] = 1; s[1] = 1; s[2] = 1;
	v = json_get(node, "translation");
	if (v) t = vec3(json_as_number(json_at(v, 0)), json_as_number(json_at(v, 1)), json_as_number(json_at(v, 2)));
	v = json_get(node, "rotation");
	if (v) r = (t_vec4){json_as_number(json_at(v, 0)), json_as_number(json_at(v, 1)), json_as_number(json_at(v, 2)), json_as_number(json_at(v, 3))};
	v = json_get(node, "scale");
	if (v) { s[0] = json_as_number(json_at(v, 0)); s[1] = json_as_number(json_at(v, 1)); s[2] = json_as_number(json_at(v, 2)); }
	return (make_transform(t, r, s));
}

t_mat4	glb_compute_world_transform(t_json_value *json, size_t node_idx)
{
	t_json_value	*nodes;
	t_json_value	*node;
	t_mat4			local;
	t_index			parent;

	nodes = json_get(json, "nodes");
	node = json_at(nodes, node_idx);
	if (!node)
		return (mat4_identity());
	local = glb_node_transform(node);
	{
		t_index	rs;

		rs = find_parent_node(json, node_idx);
		if (rs.error)
		{
			t_mat4 root_rot = mat4_identity();
			root_rot.m[1][1] = 0; root_rot.m[1][2] = -1;
			root_rot.m[2][1] = 1; root_rot.m[2][2] = 0;
			return (mat4_mul(root_rot, local));
		}
		parent = rs;
	}
	return (mat4_mul(glb_compute_world_transform(json, parent.i), local));
}
