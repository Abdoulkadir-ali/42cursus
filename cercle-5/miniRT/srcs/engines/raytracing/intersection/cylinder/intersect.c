/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:08:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	intersect_cap(const t_ray *ray, t_vec3 center, t_vec3 normal,
		double radius, double *t_out, t_hit *hit)
{
	double	denom;
	double	t;
	t_vec3	p;

	denom = vec3_dot(normal, ray->direction);
	if (fabs(denom) < EPSILON)
		return (false);
	t = vec3_dot(vec3_sub(center, ray->origin), normal) / denom;
	if (t < EPSILON || t >= *t_out)
		return (false);
	p = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	if (vec3_mag_sq(vec3_sub(p, center)) > radius * radius)
		return (false);
	*t_out = t;
	hit->t = t;
	hit->point = p;
	hit->normal = normal;
	return (true);
}

bool	intersect_cylinder(const t_ray *ray, t_primitive_array *p, int i, t_hit *h)
{
	t_cylinder cy = unpack_cylinder(p, i);
	t_vec3	oc, v;
	double	a, b, c, delta, t1, t2, best_t, y;
	bool	hit = false;

	oc = vec3_sub(ray->origin, cy.pos);
	best_t = 1e30;

	a = vec3_dot(ray->direction, ray->direction) - pow(vec3_dot(ray->direction, cy.axis), 2);
	b = 2.0 * (vec3_dot(ray->direction, oc) - vec3_dot(ray->direction, cy.axis) * vec3_dot(oc, cy.axis));
	c = vec3_dot(oc, oc) - pow(vec3_dot(oc, cy.axis), 2) - cy.radius * cy.radius;
	delta = b * b - 4 * a * c;
	if (delta >= 0)
	{
		t1 = (-b - sqrt(delta)) / (2.0 * a);
		t2 = (-b + sqrt(delta)) / (2.0 * a);
		for (int j = 0; j < 2; j++) {
			double t = (j == 0) ? t1 : t2;
			if (t > EPSILON && t < best_t) {
				v = vec3_add(ray->origin, vec3_scale(ray->direction, t));
				y = vec3_dot(vec3_sub(v, cy.pos), cy.axis);
				if (y >= 0 && y <= cy.height) {
					best_t = t; h->t = t; h->point = v;
					h->normal = vec3_norm(vec3_sub(vec3_sub(v, cy.pos), vec3_scale(cy.axis, y)));
					hit = true;
				}
			}
		}
	}
	if (intersect_cap(ray, cy.pos, vec3_scale(cy.axis, -1.0), cy.radius, &best_t, h))
		hit = true;
	if (intersect_cap(ray, vec3_add(cy.pos, vec3_scale(cy.axis, cy.height)), cy.axis, cy.radius, &best_t, h))
		hit = true;
	if (hit)
	{
		if (vec3_dot(ray->direction, h->normal) > 0)
			h->normal = vec3_scale(h->normal, -1.0);
		h->mat_idx = cy.mat_idx; h->type = TYPE_CYLINDER;
		vec3_orthonormal_basis(h->normal, &h->tangent, &h->bitangent);
	}
	return (hit);
}
