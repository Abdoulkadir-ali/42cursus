/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:09:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 03:09:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Iterative traversal for finding the closest intersection.
** Sorts children to visit closer nodes first (Early Z-Culling).
*/
t_child_intersections	get_child_intersections(const t_bvh_node *node,
							const t_ray *ray)
{
	t_child_intersections	res;

	res.h_l = false;
	if (node->left)
	{
		res.h_l = aabb_intersect_fast(&node->left->bbox, ray,
				&res.left_t.x, &res.left_t.y);
		res.left_t.x = (res.left_t.x < 0.0) ? 0.0 : res.left_t.x;
	}
	res.h_r = false;
	if (node->right)
	{
		res.h_r = aabb_intersect_fast(&node->right->bbox, ray,
				&res.right_t.x, &res.right_t.y);
		res.right_t.x = (res.right_t.x < 0.0) ? 0.0 : res.right_t.x;
	}
	return (res);
}
