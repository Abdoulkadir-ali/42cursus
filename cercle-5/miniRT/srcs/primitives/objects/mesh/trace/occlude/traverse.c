/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

static size_t	process_occ_node(t_mesh *mesh, size_t node_idx,
		const t_ray *ray, t_occ *occ)
{
	t_mbvh_node	*node;
	t_index		idx;

	node = &mesh->bvh_nodes[node_idx];
	if (node->count > 0)
	{
		if (leaf_occluded(mesh, node, ray, occ->dist))
			return (0);
		if (occ->top == 0)
			return (0);
		return (occ->stack[--occ->top]);
	}
	idx = init_index(node_idx, false);
	node_idx = pick_occ_children(mesh, idx, ray, occ);
	if (node_idx == 0 && occ->top > 0)
		return (occ->stack[--occ->top]);
	return (node_idx);
}

bool	traverse_occlude(t_mesh *mesh, const t_ray *ray, double dist)
{
	t_occ	occ;
	size_t	node_idx;

	occ.top = 0;
	occ.dist = dist;
	node_idx = 1;
	while (node_idx != 0)
	{
		node_idx = process_occ_node(mesh, node_idx - 1, ray, &occ);
		if (node_idx == 0 && occ.top == 0)
		{
			if (leaf_occluded(mesh, &mesh->bvh_nodes[0], ray, dist))
				return (true);
		}
	}
	return (false);
}
