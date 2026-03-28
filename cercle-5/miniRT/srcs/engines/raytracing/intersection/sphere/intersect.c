/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:08:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief DOD-compliant ray-sphere intersection logic for SoA storage.
 * Uses the shared unpacker to bridge SoA to a scratch t_sphere.
 */
bool	intersect_sphere(const t_ray *ray, t_primitive_array *p,
		int i, t_hit *h)
{
	t_sphere sp = unpack_sphere(p, i);
	t_vec3	oc;
	double	b, c, delta, t;

	oc = vec3_sub(ray->origin, sp.center);
	b = 2.0 * vec3_dot(oc, ray->direction);
	c = vec3_dot(oc, oc) - (sp.radius * sp.radius);
	delta = b * b - 4.0 * c;
	if (delta < 0)
		return (false);
	delta = sqrt(delta);
	t = (-b - delta) / 2.0;
	if (t < EPSILON)
		t = (-b + delta) / 2.0;
	if (t < EPSILON)
		return (false);
	h->t = t;
	h->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	h->normal = vec3_norm(vec3_sub(h->point, sp.center));
	get_sphere_uv(h->normal, &h->u, &h->v);
	vec3_orthonormal_basis(h->normal, &h->tangent, &h->bitangent);
	h->mat_idx = sp.mat_idx;
	h->type = TYPE_SPHERE;
	return (true);
}
