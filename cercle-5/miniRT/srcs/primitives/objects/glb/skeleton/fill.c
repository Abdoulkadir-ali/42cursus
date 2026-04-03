/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:21:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:21:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	build_parent_map(t_json_value *nodes, size_t *parent_map, size_t nc)
{
	t_json_value	*node;
	t_json_value	*children;
	size_t			i;
	size_t			k;
	size_t			child_idx;

	i = -1;
	while (++i < nc && i < PARSER_BUF_SIZE)
	{
		node = json_at(nodes, i);
		children = json_get(node, "children");
		if (children)
		{
			k = -1;
			while (++k < children->u.array.count)
			{
				child_idx = json_as_number(json_at(children, k));
				if (child_idx < PARSER_BUF_SIZE)
					parent_map[child_idx] = i;
			}
		}
	}
}

static int	find_joint_ancestor(t_mesh *mesh, size_t *is_joint,
				size_t *parent_map, size_t node_idx)
{
	size_t	par_idx;
	size_t	k;

	par_idx = parent_map[node_idx];
	while (par_idx < PARSER_BUF_SIZE)
	{
		if (is_joint[par_idx])
		{
			k = -1;
			while (++k < mesh->bone_count)
			{
				if (mesh->skeleton[k].node_idx == par_idx)
					return (k);
			}
			return (-1);
		}
		par_idx = parent_map[par_idx];
	}
	return (-1);
}

static void	add_non_joint_bones(t_mesh *mesh, t_json_value *nodes,
				size_t *is_joint, size_t *parent_map)
{
	size_t			i;
	t_json_value	*node;
	t_bone			*bone;

	i = -1;
	while (++i < nodes->u.array.count && i < PARSER_BUF_SIZE)
	{
		node = json_at(nodes, i);
		if (!is_joint[i] && !json_get_size_t(node, "mesh").error)
		{
			bone = &mesh->skeleton[mesh->bone_count];
			ft_memset(bone, 0, sizeof(t_bone));
			bone->node_idx = i;
			bone->parent = find_joint_ancestor(mesh, is_joint, parent_map, i);
			fill_bone_trs(bone, node);
			mesh->bone_matrices[mesh->bone_count] = mat4_identity();
			mesh->bone_count++;
		}
	}
}

/**
 * Fills extra skeleton slots for non-joint GLTF nodes that reference a mesh.
 */
static void	prepare_fill_state(size_t *state[2], t_json_value *joints)
{
	size_t	i;
	size_t	idx;

	i = -1;
	while (++i < PARSER_BUF_SIZE)
		state[1][i] = -1;
	i = -1;
	while (++i < joints->u.array.count)
	{
		idx = json_as_number(json_at(joints, i));
		if (idx < PARSER_BUF_SIZE)
			state[0][idx] = 1;
	}
}

void	glb_fill_extra_anim_nodes(t_mesh *m, t_json_value *j)
{
	size_t			*state[2];
	t_json_value	*nodes;
	t_json_value	*joints;

	nodes = json_get(j, "nodes");
	joints = json_get(json_at(json_get(j, "skins"), 0), "joints");
	if (!m->skeleton || !nodes || !joints)
		return ;
	state[0] = ft_calloc(PARSER_BUF_SIZE, sizeof(size_t));
	state[1] = malloc(sizeof(size_t) * PARSER_BUF_SIZE);
	if (!state[0] || !state[1])
	{
		free(state[0]);
		free(state[1]);
		return ;
	}
	prepare_fill_state(state, joints);
	build_parent_map(nodes, state[1], nodes->u.array.count);
	add_non_joint_bones(m, nodes, state[0], state[1]);
	free(state[0]);
	free(state[1]);
}
