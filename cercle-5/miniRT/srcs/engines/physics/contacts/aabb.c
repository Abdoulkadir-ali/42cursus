/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:24:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Checks if two Axis-Aligned Bounding Boxes overlap.
 */
bool	aabb_overlap(t_aabb a, t_aabb b)
{
	if (a.max.x < b.min.x || a.min.x > b.max.x)
		return (false);
	if (a.max.y < b.min.y || a.min.y > b.max.y)
		return (false);
	if (a.max.z < b.min.z || a.min.z > b.max.z)
		return (false);
	return (true);
}

/**
 * @brief Checks if an AABB and a sphere overlap.
 */
bool	aabb_v_sphere(t_aabb a, t_vec3 center, double radius)
{
	double	dist_sq;
	double	v;

	dist_sq = 0.0;
	v = center.x;
	if (v < a.min.x)
		dist_sq += (a.min.x - v) * (a.min.x - v);
	if (v > a.max.x)
		dist_sq += (v - a.max.x) * (v - a.max.x);
	v = center.y;
	if (v < a.min.y)
		dist_sq += (a.min.y - v) * (a.min.y - v);
	if (v > a.max.y)
		dist_sq += (v - a.max.y) * (v - a.max.y);
	v = center.z;
	if (v < a.min.z)
		dist_sq += (a.min.z - v) * (a.min.z - v);
	if (v > a.max.z)
		dist_sq += (v - a.max.z) * (v - a.max.z);
	return (dist_sq <= (radius * radius));
}
