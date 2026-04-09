/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 10:46:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:16:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"


static t_mat4	parse_node_matrix(t_json_value *v)
{
	t_mat4	m;
	int		j;

	j = 0;
	while (j < 16)
	{
		m.m[j % 4][j / 4] = json_as_number(json_at(v, j));
		j++;
	}
	return (m);
}

static void	load_node_rot_scale(t_json_value *node, t_vec4 *r, double s[3])
{
	t_json_value	*v;

	v = json_get(node, "rotation");
	if (v)
	{
		r->x = json_as_number(json_at(v, 0));
		r->y = json_as_number(json_at(v, 1));
		r->z = json_as_number(json_at(v, 2));
		r->w = json_as_number(json_at(v, 3));
	}
	v = json_get(node, "scale");
	if (v)
	{
		s[0] = json_as_number(json_at(v, 0));
		s[1] = json_as_number(json_at(v, 1));
		s[2] = json_as_number(json_at(v, 2));
	}
}

static t_mat4	extract_trs(t_json_value *node)
{
	t_vec3			t;
	t_vec4			r;
	double			s[3];
	t_json_value	*v;

	t = vec3(0, 0, 0);
	r = (t_vec4){0, 0, 0, 1};
	s[0] = 1;
	s[1] = 1;
	s[2] = 1;
	v = json_get(node, "translation");
	if (v)
		t = vec3(json_as_number(json_at(v, 0)),
				json_as_number(json_at(v, 1)), json_as_number(json_at(v, 2)));
	load_node_rot_scale(node, &r, s);
	return (make_transform(t, r, s));
}

t_mat4	glb_node_transform(t_json_value *node)
{
	t_json_value	*v;

	v = json_get(node, "matrix");
	if (v && v->type == JSON_ARRAY && v->u.array.count >= 16)
		return (parse_node_matrix(v));
	return (extract_trs(node));
}

t_mat4	glb_compute_world_transform(t_json_value *json, size_t node_idx)
{
	t_json_value	*nodes;
	t_json_value	*node;
	t_mat4			local;
	t_index			parent;
	t_mat4			root_rot;

	nodes = json_get(json, "nodes");
	node = json_at(nodes, node_idx);
	if (!node)
		return (mat4_identity());
	local = glb_node_transform(node);
	parent = find_parent_node(json, node_idx);
	if (parent.error)
	{
		root_rot = mat4_identity();
		root_rot.m[1][1] = 0;
		root_rot.m[1][2] = -1;
		root_rot.m[2][1] = 1;
		root_rot.m[2][2] = 0;
		return (mat4_mul(root_rot, local));
	}
	return (mat4_mul(glb_compute_world_transform(json, parent.i), local));
}
