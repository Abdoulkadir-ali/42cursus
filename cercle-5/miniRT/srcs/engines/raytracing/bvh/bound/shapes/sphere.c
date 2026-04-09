/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 11:16:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * Computes the Axis-Aligned Bounding Box for a sphere.
 */
t_aabb	sphere_aabb(const t_sphere *sp)
{
	t_aabb	bbox;
	double	base;
	double	rx;
	double	ry;
	double	rz;

	base = sqrt(sp->radius_sq);
	rx = base * fmax(fabs(sp->transform.scale.x), 1e-4);
	ry = base * fmax(fabs(sp->transform.scale.y), 1e-4);
	rz = base * fmax(fabs(sp->transform.scale.z), 1e-4);
	bbox.min = vec3_sub(sp->transform.pos, vec3(rx, ry, rz));
	bbox.max = vec3_add(sp->transform.pos, vec3(rx, ry, rz));
	return (bbox);
}
