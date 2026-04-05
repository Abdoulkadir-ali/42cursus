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
			return ((size_t)-1);
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
	static int	_occ_logged = 0;

	if (!_occ_logged)
	{
		ft_print_debug("[OCC] traverse_occlude first call, tri_count=%zu\n",
			mesh->tri_count);
		fflush(stdout);
		_occ_logged = 1;
	}
	occ.top = 0;
	occ.dist = dist;
	node_idx = 1;
	while (node_idx != 0)
	{
		node_idx = process_occ_node(mesh, node_idx - 1, ray, &occ);
		if (node_idx == (size_t)-1)
			return (true);
		if (node_idx != 0)
			node_idx++;
		if (node_idx == 0 && occ.top == 0)
			break ;
	}
	return (false);
}
