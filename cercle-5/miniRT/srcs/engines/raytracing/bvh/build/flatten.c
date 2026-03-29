/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flatten.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:07:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 12:36:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "debug.h"

/**
 * @brief Allocates the final flat arrays for the BVH tree.
 * @param bvh Pointer to the BVH structure.
 * @param k Total number of objects (leaves) in the tree.
 * @return Returns true if allocation succeeded.
 * @note Uses posix_memalign for 32-byte alignment required by t_bvh_node.
 */
bool	alloc_flat(t_bvh *bvh, size_t k)
{
	size_t	alloc_size;
	void	*ptr;
	int		ret;

	ptr = NULL;
	alloc_size = k * 2 * sizeof(t_bvh_node);
	DBG_TRACE_MSG(DBG_CH_BVH, "alloc_flat: k=%zu nodes=%zu size=%zu\n",
		k, k * 2, alloc_size);
	ret = posix_memalign(&ptr, 32, alloc_size);
	if (ret == 0 && ptr)
	{
		ft_memset(ptr, 0, alloc_size);
		bvh->nodes = ptr;
	}
	else
		bvh->nodes = NULL;
	DBG_TRACE_MSG(DBG_CH_BVH, "alloc_flat: bvh->nodes=%p aligned=%d\n",
		(void*)bvh->nodes, ((size_t)bvh->nodes % 32) == 0);
	bvh->refs = NULL;
	return (bvh->nodes != NULL);
}

static void	flatten_leaf(t_bvh_tmp_node *n, t_bvh *bvh, int my_idx, int *rc)
{
	(void)rc;
	bvh->nodes[my_idx].count = (int)n->num_refs;
	bvh->nodes[my_idx].left_or_first = n->first_ref;
}

/**
 * @brief Recursively flattens the pointer-based temporary tree into the flat 
 * array used for fast traversal.
 */
void	flatten_tmp(t_bvh_tmp_node *node, t_bvh *bvh, int *nc, int *rc)
{
	int	my_idx;
	int	right_idx;

	if (!node)
		return ;
	DBG_TRACE_MSG(DBG_CH_BVH, "flatten: nc=%d node=%p\n", *nc, (void*)node);
	my_idx = (*nc)++;
	DBG_TRACE_MSG(DBG_CH_BVH, "flatten: my_idx=%d nodes=%p\n", my_idx, (void*)bvh->nodes);
	DBG_TRACE_MSG(DBG_CH_BVH, "flatten: node->bbox min=(%f,%f,%f)\n",
		node->bbox.min.x, node->bbox.min.y, node->bbox.min.z);
	bvh->nodes[my_idx].bbox = node->bbox;
	DBG_TRACE_MSG(DBG_CH_BVH, "flatten: bbox copied num_refs=%d\n", node->num_refs);
	if (node->num_refs > 0)
		flatten_leaf(node, bvh, my_idx, rc);
	else
	{
		bvh->nodes[my_idx].count = 0;
		if (node->left)
			flatten_tmp(node->left, bvh, nc, rc);
		right_idx = *nc;
		if (node->right)
			flatten_tmp(node->right, bvh, nc, rc);
		bvh->nodes[my_idx].left_or_first = right_idx;
	}
}
