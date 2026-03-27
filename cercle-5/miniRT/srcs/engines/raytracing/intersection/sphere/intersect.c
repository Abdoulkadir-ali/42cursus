/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 02:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief DOD-compliant ray-sphere intersection logic for SoA storage.
 * Directly accesses parallel arrays for positions and radii.
 */
static void	setup_quadratic(const t_ray *r, t_primitive_array *p, int i, t_quadratic *q)
{
	t_vec3	oc;

	oc = vec3_sub(r->origin, p->positions[i]);
	q->a = vec3_dot(r->direction, r->direction);
	q->b = 2.0 * vec3_dot(oc, r->direction);
	q->c = vec3_dot(oc, oc) - (p->radii[i] * p->radii[i]);
}

/**
 * @brief Selects the closest hit-t from quadratic roots.
 */
static bool	select_t(t_quadratic_roots roots, double *t)
{
	if (roots.t1 > EPSILON)
		*t = roots.t1;
	else
		*t = roots.t2;
	return (*t > EPSILON);
}

/**
 * @brief Calculates hit details for the intersected sphere.
 */
static void	set_hit_data(const t_ray *r, t_primitive_array *p, int i, t_hit *h)
{
	t_vec3	local_n;

	h->point = vec3_add(r->origin, vec3_scale(r->direction, h->t));
	local_n = vec3_norm(vec3_sub(h->point, p->positions[i]));
	h->normal = local_n;
	get_sphere_uv(local_n, &h->u, &h->v);
	vec3_orthonormal_basis(h->normal, &h->tangent, &h->bitangent);
	h->mat_idx = p->mat_ids[i];
	h->type = PRIM_SPHERE;
}

/**
 * @brief High-performance ray-sphere intersection for 100% DOD.
 */
bool	intersect_sphere(const t_ray *ray, t_primitive_array *prims, 
		int idx, t_hit *hit)
{
	t_quadratic			q;
	t_quadratic_roots	roots;

	setup_quadratic(ray, prims, idx, &q);
	if (!solve_quadratic(q, &roots))
		return (false);
	if (!select_t(roots, &hit->t))
		return (false);
	set_hit_data(ray, prims, idx, hit);
	return (true);
}
