/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabbhit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 04:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 03:44:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief Computes the intersection time (t0 or t1) between a ray and a node's Axis-Aligned Bounding Box (AABB) within the BVH tree.
 * 
 * Validates the node index and executes a fast slab-method AABB intersection
 * check (`aabb_intersect_fast`). It handles edge cases, such as an origin
 * resting inside the box (resulting in `t0` clamping to `0.0`). The intersection
 * is rejected if the computed hit is beyond the `max_t` boundary limitation.
 * 
 * @param bvh        A constant pointer to the entire state of the BVH tree holding bounding boxes.
 * @param idx        The target index of the BVH node holding the `t_bbox` to test against.
 * @param ray        A constant pointer to the ray struct (containing origin and direction).
 * @param max_t      The maximum valid traveling distance/time `t` acceptable for this BVH traversal.
 * 
 * @return Returns the hit time `t0` (propagated to `t1` format) if valid. Otherwise, returns `-1.0`.
 */
double	aabb_hit_time_or_neg1(const t_bvh *bvh, int idx, const t_ray *ray,
		double max_t)
{
	double	t0;
	double	t1;

	if (idx < 0)
		return (-1.0);
	if (!aabb_intersect_fast(&bvh->nodes[idx].bbox, ray, &t0, &t1))
		return (-1.0);
	if (t0 < 0.0)
		t0 = 0.0;
	if (t0 >= max_t)
		return (-1.0);
	t1 = t0 + 0.0;
	return (t1);
}
