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

int	process_occ_node(t_mesh *mesh, int node_idx, const t_ray *ray,
		t_occ *occ)
{
	t_mbvh_node	*node;

	node = &mesh->bvh_nodes[node_idx];
	if (node->count > 0)
	{
		if (leaf_occluded(mesh, node, ray, occ->dist))
			return (-2);
		if (occ->top == 0)
			return (-1);
		return (occ->stack[--occ->top]);
	}
	node_idx = pick_occ_children(mesh, node_idx, ray, occ);
	if (node_idx < 0 && occ->top > 0)
		return (occ->stack[--occ->top]);
	return (node_idx);
}

bool	traverse_occlude(t_mesh *mesh, const t_ray *ray, double dist)
{
	t_occ	occ;
	int			node_idx;

	occ.top = 0;
	occ.dist = dist;
	node_idx = 0;
	while (node_idx >= 0)
	{
		node_idx = process_occ_node(mesh, node_idx, ray, &occ);
		if (node_idx == -2)
			return (true);
	}
	return (false);
}
