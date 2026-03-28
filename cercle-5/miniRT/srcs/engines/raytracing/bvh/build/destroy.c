/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:04:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:30:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief Recursively destroys a pointer-based temporary BVH building tree.
 */
void	node_destroy(t_bvh_tmp_node *node)
{
	if (!node)
		return ;
	node_destroy(node->left);
	node_destroy(node->right);
	free(node);
}

/**
 * @brief Destroys and cleans up all resources associated with the final BVH tree.
 */
void	bvh_destroy(t_bvh *bvh)
{
	if (!bvh)
		return ;
	free(bvh->nodes);
	free(bvh->refs);
	free(bvh);
}
