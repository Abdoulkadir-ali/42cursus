/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * Computes the Axis-Aligned Bounding Box for a sphere.
 */
t_aabb	sphere_aabb(t_sphere *sp)
{
	t_aabb	bbox;
	double	r;

	/* Scale-aware AABB for Deformed Spheres (Ellipsoids) */
	double s_max = fmax(fabs(sp->transform.scale.x), 
			fmax(fabs(sp->transform.scale.y), fabs(sp->transform.scale.z)));
	if (s_max < 1e-4) s_max = 1.0; /* Handle uninitialized scale */

	r = sqrt(sp->radius_sq) * s_max;
	bbox.min = vec3_sub(sp->transform.pos, vec3(r, r, r));
	bbox.max = vec3_add(sp->transform.pos, vec3(r, r, r));
	return (bbox);
}
