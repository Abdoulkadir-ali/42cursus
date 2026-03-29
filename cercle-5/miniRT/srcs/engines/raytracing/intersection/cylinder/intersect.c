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
	t_vec3	pos = vec3(p->px[i], p->py[i], p->pz[i]);
	t_vec3	axis = vec3(p->ax[i], p->ay[i], p->az[i]);
	double	radius = p->radii[i];
	double	height = p->heights[i];
	int		mat_idx = p->mat_ids[i];
	t_vec3	oc, v;
	double	a, b, c, delta, t1, t2, best_t, y;
	bool	hit = false;

	oc = vec3_sub(ray->origin, pos);
	best_t = 1e30;

	a = vec3_dot(ray->direction, ray->direction)
		- (vec3_dot(ray->direction, axis) * vec3_dot(ray->direction, axis));
	b = 2.0 * (vec3_dot(ray->direction, oc)
			- vec3_dot(ray->direction, axis) * vec3_dot(oc, axis));
	c = vec3_dot(oc, oc) - (vec3_dot(oc, axis) * vec3_dot(oc, axis))
		- radius * radius;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		DBG_TRACE_MSG(DBG_CH_RENDER,
			"intersect_cylinder: disc<0 body miss\n");
	if (delta >= 0)
	{
		t1 = (-b - sqrt(delta)) / (2.0 * a);
		t2 = (-b + sqrt(delta)) / (2.0 * a);
		if (t1 > EPSILON && t1 < best_t)
		{
			v = vec3_add(ray->origin, vec3_scale(ray->direction, t1));
			y = vec3_dot(vec3_sub(v, pos), axis);
			if (y >= 0 && y <= height)
			{
				best_t = t1;
				h->t = t1;
				h->point = v;
				h->normal = vec3_norm(vec3_sub(vec3_sub(v, pos),
							vec3_scale(axis, y)));
				hit = true;
			}
		}
		if (t2 > EPSILON && t2 < best_t)
		{
			v = vec3_add(ray->origin, vec3_scale(ray->direction, t2));
			y = vec3_dot(vec3_sub(v, pos), axis);
			if (y >= 0 && y <= height)
			{
				best_t = t2;
				h->t = t2;
				h->point = v;
				h->normal = vec3_norm(vec3_sub(vec3_sub(v, pos),
							vec3_scale(axis, y)));
				hit = true;
			}
		}
	}
	if (intersect_cap(ray, pos, vec3_scale(axis, -1.0), radius, &best_t, h))
		hit = true;
	if (intersect_cap(ray, vec3_add(pos, vec3_scale(axis, height)),
			axis, radius, &best_t, h))
		hit = true;
	if (hit)
	{
		if (vec3_dot(ray->direction, h->normal) > 0)
			h->normal = vec3_scale(h->normal, -1.0);
		h->mat_idx = mat_idx;
		h->type = TYPE_CYLINDER;
		vec3_orthonormal_basis(h->normal, &h->tangent, &h->bitangent);
		DBG_TRACE_MSG(DBG_CH_RENDER,
			"intersect_cylinder: hit t=%.4f\n", h->t);
	}
	return (hit);
}
