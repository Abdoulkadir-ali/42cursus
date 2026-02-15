/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:04:57 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 03:04:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	node_destroy(t_bvh_node *node)
{
	if (!node)
		return ;
	node_destroy(node->left);
	node_destroy(node->right);
	if (node->refs)
		free(node->refs);
	free(node);
}
