/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:50:13 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 16:50:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * Computes the Axis-Aligned Bounding Box for a sphere.
 */
t_aabb	sphere_aabb(t_sphere *sp)
{
	t_aabb		bbox;
	double		r;
	double		s_max;

	s_max = fmax(fabs(sp->transform.scale.x),
			fmax(fabs(sp->transform.scale.y), fabs(sp->transform.scale.z)));
	if (s_max < 1e-4)
		s_max = 1.0;
	r = sqrt(sp->radius_sq) * s_max;
	bbox.min = vec3_sub(sp->transform.pos, vec3(r, r, r));
	bbox.max = vec3_add(sp->transform.pos, vec3(r, r, r));
	return (bbox);
}
