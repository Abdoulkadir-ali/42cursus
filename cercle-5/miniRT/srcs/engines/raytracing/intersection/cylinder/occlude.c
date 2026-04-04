/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occlude.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 20:46:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief Validates a body-hit candidate at parameter t.
 */
static bool	body_hit_valid(const t_ray *ray, t_cylinder *cy,
		double t, double max_t)
{
	t_vec3	p;
	double	h;

	if (t <= EPSILON || t >= max_t)
		return (false);
	p = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	h = vec3_dot(vec3_sub(p, cy->transform.pos), cy->transform.forward);
	return (h >= 0 && h <= cy->transform.scale.y);
}

/**
 * @brief Shadow test for the cylinder body (no UV or normal).
 */
static bool	occlude_cy_body(const t_ray *ray, t_cylinder *cy, double max_t)
{
	t_quadratic			q;
	t_quadratic_roots	roots;
	t_vec3				oc;
	double				dd;

	oc = vec3_sub(ray->origin, cy->transform.pos);
	dd = vec3_dot(ray->direction, cy->transform.forward);
	q.a = vec3_dot(ray->direction, ray->direction) - dd * dd;
	q.b = 2.0 * (vec3_dot(ray->direction, oc) - dd
			* vec3_dot(oc, cy->transform.forward));
	q.c = vec3_dot(oc, oc) - vec3_dot(oc, cy->transform.forward)
		* vec3_dot(oc, cy->transform.forward)
		- cy->radius_sq;
	if (!solve_quadratic(q, &roots))
		return (false);
	return (body_hit_valid(ray, cy, roots.t1, max_t)
		|| body_hit_valid(ray, cy, roots.t2, max_t));
}

/**
 * @brief Shadow test for a single cylinder cap (no UV or normal).
 */
static bool	occlude_cy_cap(const t_ray *ray, t_cylinder *cy,
		t_vec3 center, double max_t)
{
	double	denom;
	double	t;
	t_vec3	p;

	denom = vec3_dot(ray->direction, cy->transform.forward);
	if (fabs(denom) < 1e-6)
		return (false);
	t = vec3_dot(vec3_sub(center, ray->origin),
			cy->transform.forward) / denom;
	if (t <= EPSILON || t >= max_t)
		return (false);
	p = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	return (vec3_mag_sq(vec3_sub(p, center))
		<= cy->radius_sq);
}

/**
 * @brief Any-hit test for shadow rays against a cylinder.
 */
bool	occlude_cylinder(const t_ray *ray, t_cylinder *cy, double max_t)
{
	if (occlude_cy_body(ray, cy, max_t))
		return (true);
	if (occlude_cy_cap(ray, cy, cy->transform.pos, max_t))
		return (true);
	return (occlude_cy_cap(ray, cy, cy->top, max_t));
}
