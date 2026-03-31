/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:15:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "debug.h"

static int	build_mesh_split(t_mbvh *bvh, int first, int count,
				t_mbvh_node *node)
{
	t_bvh_split		split;
	t_bvh_try	try;
	int				mid;

	try.bvh = bvh;
	try.node = node;
	try.first = first;
	try.count = count;
	try.split = &split;
	try.mid = &mid;
	if (!bvh_try_split(&try))
		return (bvh_make_leaf(node, first, count, bvh->node_count - 1));
	node->count = 0;
	node->axis = split.axis;
	build_mesh_recursive(bvh, first, mid);
	node->left_or_first = build_mesh_recursive(bvh, first + mid, count - mid);
	debug_print_bvh_build(count, 0, false);
	return (bvh->node_count - 1);
}

/**
 * Recursively builds the BVH tree using top-down spatial partitioning. 
 * It automatically decides between creating a leaf node or continuing 
 * the split based on item count and SAH cost.
 */
int	build_mesh_recursive(t_mbvh *bvh, int first, int count)
{
	t_mbvh_node		*node;
	int				node_idx;

	node_idx = bvh->node_count++;
	node = &bvh->nodes[node_idx];
	bvh_update_node_bounds(node, bvh, first, count);
	if (count <= 4)
		return (bvh_make_leaf(node, first, count, node_idx));
	return (build_mesh_split(bvh, first, count, node));
}
