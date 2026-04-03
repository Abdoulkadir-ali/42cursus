/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:15:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:30:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "debug.h"

#include "mesh.h"
#include "debug.h"

static size_t	build_mesh_split(t_mbvh *bvh, size_t first, size_t count,
		t_mbvh_node *node)
{
	t_bvh_split		split;
	t_bvh_try		try;
	size_t			mid;

	try.bvh = bvh;
	try.node = node;
	try.first = first;
	try.count = count;
	try.split = &split;
	try.mid = &mid;
	if (!bvh_try_split(&try))
		return (bvh_make_leaf(node, first, count,
				init_index(bvh->node_count - 1, false)));
	node->count = 0;
	node->axis = split.axis;
	build_mesh_recursive(bvh, first, mid);
	node->left_or_first = build_mesh_recursive(bvh, first + mid,
			count - mid);
	debug_print_bvh_build(count, 0, false);
	return (bvh->node_count - 1);
}

/**
 * Recursively builds the BVH tree using top-down spatial partitioning.
 * It automatically decides between creating a leaf node or continuing 
 * the split based on item count and SAH cost.
 */
size_t	build_mesh_recursive(t_mbvh *bvh, size_t first, size_t count)
{
	t_mbvh_node		*node;
	size_t			node_idx;

	node_idx = bvh->node_count++;
	node = &bvh->nodes[node_idx];
	bvh_update_node_bounds(node, bvh, first, count);
	if (count <= 4)
		return (bvh_make_leaf(node, first, count, init_index(node_idx, false)));
	return (build_mesh_split(bvh, first, count, node));
}
