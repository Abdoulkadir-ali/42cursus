/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:10:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static double	intersect_sph(const t_ray *r, t_vec3 c, double rad_sq)
{
	t_vec3	oc;
	double	b;
	double	cc;
	double	h;
	double	t1;
	double	t2;

	oc = vec3_sub(r->origin, c);
	b = vec3_dot(oc, r->direction);
	cc = vec3_dot(oc, oc) - rad_sq;
	h = b * b - cc;
	if (h < 0.0)
		return (-1.0);
	h = sqrt(h);
	t1 = -b - h;
	if (t1 > EPSILON)
		return (t1);
	t2 = -b + h;
	if (t2 > EPSILON)
		return (t2);
	return (-1.0);
}

bool	intersect_capsule(const t_ray *ray, t_primitive_array *p, int i,
		t_hit *hit)
{
	t_capsule ca = unpack_capsule(p, i);
	t_vec3	ba, oa, pa;
	double	ba_ba, ba_rd, ba_oa, rd_rd, rd_oa, a, b, c, h, t, y, t1, t2, h_val;

	ba = vec3_sub(ca.b, ca.a);
	oa = vec3_sub(ray->origin, ca.a);
	ba_ba = vec3_dot(ba, ba);
	ba_rd = vec3_dot(ba, ray->direction);
	ba_oa = vec3_dot(ba, oa);
	rd_rd = vec3_dot(ray->direction, ray->direction);
	rd_oa = vec3_dot(ray->direction, oa);
	a = ba_ba * rd_rd - ba_rd * ba_rd;
	b = ba_ba * rd_oa - ba_rd * ba_oa;
	c = ba_ba * vec3_dot(oa, oa) - ba_oa * ba_oa - ca.radius * ca.radius * ba_ba;
	h = b * b - a * c;
	hit->t = -1.0;
	if (h >= 0.0)
	{
		t = (-b - sqrt(h)) / a;
		y = ba_oa + t * ba_rd;
		if (y > 0.0 && y < ba_ba)
			hit->t = t;
		else
		{
			t1 = intersect_sph(ray, ca.a, ca.radius * ca.radius);
			t2 = intersect_sph(ray, ca.b, ca.radius * ca.radius);
			if (t1 > EPSILON && (t2 <= EPSILON || t1 < t2))
				hit->t = t1;
			else if (t2 > EPSILON)
				hit->t = t2;
		}
	}
	if (hit->t < EPSILON)
		return (false);
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	pa = vec3_sub(hit->point, ca.a);
	h_val = clamp_d(vec3_dot(pa, ba) / ba_ba, 0.0, 1.0);
	hit->normal = vec3_norm(vec3_sub(pa, vec3_scale(ba, h_val)));
	if (vec3_dot(ray->direction, hit->normal) > 0)
		hit->normal = vec3_scale(hit->normal, -1.0);
	hit->mat_idx = ca.mat_idx;
	hit->type = TYPE_CAPSULE;
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
	return (true);
}
