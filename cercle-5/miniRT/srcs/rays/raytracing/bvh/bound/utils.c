/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * Creates an empty AABB with inverse-infinite bounds.
 */
t_aabb	aabb_create_empty(void)
{
	t_aabb	bbox;

	bbox.min = vec3(MAX_VALUE, MAX_VALUE, MAX_VALUE);
	bbox.max = vec3(-MAX_VALUE, -MAX_VALUE, -MAX_VALUE);
	return (bbox);
}

/**
 * Computes the union of two Axis-Aligned Bounding Boxes.
 */
t_aabb	aabb_union(const t_aabb *a, const t_aabb *b)
{
	t_aabb	bbox;

	bbox.min = vec3(fmin(a->min.x, b->min.x), fmin(a->min.y, b->min.y),
			fmin(a->min.z, b->min.z));
	bbox.max = vec3(fmax(a->max.x, b->max.x), fmax(a->max.y, b->max.y),
			fmax(a->max.z, b->max.z));
	return (bbox);
}

/**
 * Expands an AABB to include a point.
 */
void	aabb_expand_point(t_aabb *bbox, t_vec3 p)
{
	bbox->min.x = fmin(bbox->min.x, p.x);
	bbox->min.y = fmin(bbox->min.y, p.y);
	bbox->min.z = fmin(bbox->min.z, p.z);
	bbox->max.x = fmax(bbox->max.x, p.x);
	bbox->max.y = fmax(bbox->max.y, p.y);
	bbox->max.z = fmax(bbox->max.z, p.z);
}

/**
 * Computes the surface area of an Axis-Aligned Bounding Box.
 */
double	aabb_surface_area(t_aabb bbox)
{
	t_vec3	d;

	d = vec3_sub(bbox.max, bbox.min);
	if (d.x < 0 || d.y < 0 || d.z < 0)
		return (0);
	return (2 * (d.x * d.y + d.y * d.z + d.z * d.x));
}
