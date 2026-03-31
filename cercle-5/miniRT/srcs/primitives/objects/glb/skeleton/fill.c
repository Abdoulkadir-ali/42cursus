/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:21:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	build_parent_map(t_json_value *nodes, int *parent_map, int nc)
{
	t_json_value	*node;
	t_json_value	*children;
	int				i;
	int				k;
	int				child_idx;

	i = -1;
	while (++i < nc && i < 65536)
	{
		node = json_at(nodes, i);
		children = json_get(node, "children");
		if (children)
		{
			k = -1;
			while (++k < (int)children->u.array.count)
			{
				child_idx = (int)json_as_number(json_at(children, k));
				if (child_idx >= 0 && child_idx < 65536)
					parent_map[child_idx] = i;
			}
		}
	}
}

static int	find_joint_ancestor(t_mesh *mesh, int *is_joint, int *parent_map,
				int node_idx)
{
	int	par_idx;
	int	k;

	par_idx = parent_map[node_idx];
	while (par_idx >= 0 && par_idx < 65536)
	{
		if (is_joint[par_idx])
		{
			k = -1;
			while (++k < mesh->bone_count)
				if (mesh->skeleton[k].node_idx == par_idx)
					return (k);
			return (-1);
		}
		par_idx = parent_map[par_idx];
	}
	return (-1);
}

static void	add_non_joint_bones(t_mesh *mesh, t_json_value *nodes,
				int *is_joint, int *parent_map)
{
	int				i;
	t_json_value	*node;
	t_bone			*bone;

	i = -1;
	while (++i < (int)nodes->u.array.count && i < 65536)
	{
		node = json_at(nodes, i);
		if (!is_joint[i] && (int)json_get_int(node, "mesh") >= 0)
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
static void	prepare_fill_state(int *state[2], t_json_value *joints)
{
	int	i;

	i = -1;
	while (++i < 65536)
		state[1][i] = -1;
	i = -1;
	while (++i < (int)joints->u.array.count)
		state[0][(int)json_as_number(json_at(joints, i))] = 1;
}

void	glb_fill_extra_anim_nodes(t_mesh *m, t_json_value *j)
{
	int				*state[2];
	t_json_value	*nodes;
	t_json_value	*joints;

	nodes = json_get(j, "nodes");
	joints = json_get(json_at(json_get(j, "skins"), 0), "joints");
	if (!m->skeleton || !nodes || !joints)
		return ;
	state[0] = ft_calloc(65536, sizeof(int));
	state[1] = malloc(sizeof(int) * 65536);
	if (!state[0] || !state[1])
	{
		free(state[0]);
		free(state[1]);
		return ;
	}
	prepare_fill_state(state, joints);
	build_parent_map(nodes, state[1], (int)nodes->u.array.count);
	add_non_joint_bones(m, nodes, state[0], state[1]);
	free(state[0]);
	free(state[1]);
}
