/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flatten.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:07:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 06:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief Allocates the final flat arrays for the BVH tree.
 * @param bvh Pointer to the BVH structure.
 * @param k Total number of objects (leaves) in the tree.
 * @return Returns true if allocation succeeded.
 */
bool	alloc_flat(t_bvh *bvh, size_t k)
{
	bvh->nodes = ft_calloc(k * 2, sizeof(t_bvh_node));
	bvh->refs = malloc(sizeof(t_bvh_ref) * k);
	return (bvh->nodes != NULL && bvh->refs != NULL);
}

static void	flatten_leaf(t_bvh_tmp_node *n, t_bvh *bvh, int my_idx, int *rc)
{
	size_t	i;

	bvh->nodes[my_idx].count = (int)n->num_refs;
	bvh->nodes[my_idx].left_or_first = *rc;
	i = 0;
	while (i < n->num_refs)
	{
		bvh->refs[(*rc)++] = n->refs[i];
		i++;
	}
}

/**
 * @brief Recursively flattens the pointer-based temporary tree into the flat 
 * array used for fast traversal.
 */
void	flatten_tmp(t_bvh_tmp_node *node, t_bvh *bvh, int *nc, int *rc)
{
	int	my_idx;
	int	right_idx;

	my_idx = (*nc)++;
	bvh->nodes[my_idx].bbox = node->bbox;
	if (node->num_refs > 0)
		flatten_leaf(node, bvh, my_idx, rc);
	else
	{
		bvh->nodes[my_idx].count = 0;
		flatten_tmp(node->left, bvh, nc, rc);
		right_idx = *nc;
		flatten_tmp(node->right, bvh, nc, rc);
		bvh->nodes[my_idx].left_or_first = right_idx;
	}
}
