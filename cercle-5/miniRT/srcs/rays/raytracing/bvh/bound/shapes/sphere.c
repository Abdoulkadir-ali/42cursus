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

	r = sqrt(sp->radius_sq);
	bbox.min = vec3_sub(sp->transform.pos, vec3(r, r, r));
	bbox.max = vec3_add(sp->transform.pos, vec3(r, r, r));
	return (bbox);
}
