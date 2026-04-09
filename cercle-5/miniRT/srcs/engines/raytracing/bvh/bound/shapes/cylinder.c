/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * Computes a tight world-space AABB for an arbitrarily oriented cylinder.
 * Works for any forward direction; center is the geometric mid-point.
 * Half-extents along each world axis i: H*|ax_i| + R*sqrt(1 - ax_i^2)
 */
t_aabb	cylinder_aabb(t_cylinder *cy)
{
	t_aabb	bbox;
	t_vec3	ax;
	t_vec3	c;
	t_vec3	e;

	ax = vec3_norm(cy->transform.forward);
	c = vec3_add(cy->transform.pos,
			vec3_scale(ax, cy->transform.scale.y * 0.5));
	e.x = (cy->transform.scale.y * 0.5) * fabs(ax.x) + cy->transform.scale.x
		* sqrt(ax.y * ax.y + ax.z * ax.z);
	e.y = (cy->transform.scale.y * 0.5) * fabs(ax.y) + cy->transform.scale.x
		* sqrt(ax.x * ax.x + ax.z * ax.z);
	e.z = (cy->transform.scale.y * 0.5) * fabs(ax.z) + cy->transform.scale.x
		* sqrt(ax.x * ax.x + ax.y * ax.y);
	bbox.min = vec3_sub(c, e);
	bbox.max = vec3_add(c, e);
	return (bbox);
}
