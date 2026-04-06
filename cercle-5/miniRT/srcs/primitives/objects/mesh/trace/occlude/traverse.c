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

static void	process_occ_node(t_mesh *mesh, t_index *idx,
		const t_ray *ray, t_occ *occ)
{
	t_mbvh_node	*node;

	node = &mesh->bvh_nodes[idx->i];
	if (node->count > 0)
	{
		if (leaf_occluded(mesh, node, ray, occ->dist))
		{
			occ->occluded = true;
			idx->error = true;
			return ;
		}
		if (occ->top == 0)
			idx->error = true;
		else
			*idx = init_index(occ->stack[--occ->top], false);
		return ;
	}
	*idx = pick_occ_children(mesh, *idx, ray, occ);
	if (idx->error && occ->top > 0)
		*idx = init_index(occ->stack[--occ->top], false);
}

bool	traverse_occlude(t_mesh *mesh, const t_ray *ray, double dist)
{
	t_occ	occ;
	t_index	idx;

	occ = (t_occ){.dist = dist};
	idx = init_index(0, false);
	while (!idx.error)
		process_occ_node(mesh, &idx, ray, &occ);
	return (occ.occluded);
}
