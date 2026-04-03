/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:15:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:04:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

/**
 * Configures a BVH node as a leaf, storing the range of triangle 
 * indices it contains.
 */
size_t	bvh_make_leaf(t_mbvh_node *node, size_t first, size_t count,
			t_index idx)
{
	(void)idx;
	node->left_or_first = first;
	node->count = count;
	return (idx.i);
}
