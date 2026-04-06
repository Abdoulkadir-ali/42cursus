/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:21:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:40:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	build_parent_map(t_json_value *nodes, t_index *parent_map, size_t nc)
{
	t_json_value	*node;
	t_json_value	*children;
	size_t			i;
	size_t			k;

	i = 0;
	while (i < nc && i < PARSER_BUF_SIZE)
	{
		node = json_at(nodes, i);
		children = json_get(node, "children");
		if (children)
		{
			k = 0;
			while (k < children->u.array.count)
			{
				t_index	rs;

				rs = json_as_t_index(json_at(children, k));
				if (!rs.error && rs.i < PARSER_BUF_SIZE)
					parent_map[rs.i] = init_index(i, false);
				k++;
			}
		}
		i++;
	}
}

static t_index	find_joint_ancestor(t_mesh *mesh, t_index *is_joint,
				t_index *parent_map, size_t node_idx)
{
	t_index	par;
	t_index	k;

	par = parent_map[node_idx];
	while (!par.error && par.i < PARSER_BUF_SIZE)
	{
		if (!is_joint[par.i].error)
		{
			k = init_index(0, false);
			while (k.i < mesh->bone_count)
			{
				if (mesh->skeleton[k.i].node_idx == par.i)
					return (k);
				k.i++;
			}
			return (init_index(0, true));
		}
		par = parent_map[par.i];
	}
	return (init_index(0, true));
}

static void	add_non_joint_bones(t_mesh *mesh, t_json_value *nodes,
				t_index *is_joint, t_index *parent_map)
{
	size_t			i;
	t_json_value	*node;
	t_bone			*bone;

	i = 0;
	while (i < nodes->u.array.count && i < PARSER_BUF_SIZE)
	{
		node = json_at(nodes, i);
		if (is_joint[i].error && !json_get_size_t(node, "mesh").error)
		{
			bone = &mesh->skeleton[mesh->bone_count];
			ft_memset(bone, 0, sizeof(t_bone));
			bone->node_idx = i;
			bone->parent = find_joint_ancestor(mesh, is_joint, parent_map, i);
			fill_bone_trs(bone, node);
			mesh->bone_matrices[mesh->bone_count] = mat4_identity();
			mesh->bone_count++;
		}
		i++;
	}
}

static void	prepare_fill_state(t_vec2s state, t_json_value *joints)
{
	size_t	i;

	i = 0;
	while (i < PARSER_BUF_SIZE)
	{
		((t_index *)state.y)[i] = init_index(0, true);
		((t_index *)state.x)[i] = init_index(0, true);
		i++;
	}
	i = 0;
	while (i < joints->u.array.count)
	{
		t_index	rs;

		rs = json_as_t_index(json_at(joints, i));
		if (!rs.error && rs.i < PARSER_BUF_SIZE)
			((t_index *)state.x)[rs.i] = init_index(1, false);
		i++;
	}
}

void	glb_fill_extra_anim_nodes(t_mesh *m, t_json_value *j)
{
	t_vec2s			state;
	t_json_value	*nodes;
	t_json_value	*joints;

	nodes = json_get(j, "nodes");
	joints = json_get(json_at(json_get(j, "skins"), 0), "joints");
	if (!m->skeleton || !nodes || !joints)
		return ;
	state.x = (size_t)ft_calloc(PARSER_BUF_SIZE, sizeof(t_index));
	state.y = (size_t)ft_calloc(PARSER_BUF_SIZE, sizeof(t_index));
	if (!state.x || !state.y)
	{
		free((void *)state.x);
		free((void *)state.y);
		return ;
	}
	prepare_fill_state(state, joints);
	build_parent_map(nodes, (t_index *)state.y, nodes->u.array.count);
	add_non_joint_bones(m, nodes, (t_index *)state.x, (t_index *)state.y);
	free((void *)state.x);
	free((void *)state.y);
}
