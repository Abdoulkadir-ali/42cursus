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
	t_vec3	center;
	double	r;
	double	h;
	double	ex;
	double	ey;
	double	ez;

	ax = vec3_norm(cy->transform.forward);
	r = cy->transform.scale.x;
	h = cy->transform.scale.y * 0.5;
	center = vec3_add(cy->transform.pos, vec3_scale(ax, h));
	ex = h * fabs(ax.x) + r * sqrt(ax.y * ax.y + ax.z * ax.z);
	ey = h * fabs(ax.y) + r * sqrt(ax.x * ax.x + ax.z * ax.z);
	ez = h * fabs(ax.z) + r * sqrt(ax.x * ax.x + ax.y * ax.y);
	bbox.min = vec3_sub(center, vec3(ex, ey, ez));
	bbox.max = vec3_add(center, vec3(ex, ey, ez));
	return (bbox);
}
