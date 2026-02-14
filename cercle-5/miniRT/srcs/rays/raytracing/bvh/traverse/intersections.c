/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
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

	res.h_l = node->left && aabb_intersect_fast(&node->left->bbox, ray,
			&res.left_t.x, &res.left_t.y);
	res.h_r = node->right && aabb_intersect_fast(&node->right->bbox, ray,
			&res.right_t.x, &res.right_t.y);
	return (res);
}
