/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:46:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:35:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	bvh_destroy(t_bvh *bvh)
{
	if (!bvh)
		return ;
	free(bvh->nodes);
	free(bvh->refs);
	free(bvh);
}

void	node_destroy(t_bvh_tmp_node *node)
{
	if (!node)
		return ;
	node_destroy(node->left);
	node_destroy(node->right);
	free(node->refs);
	free(node);
}
