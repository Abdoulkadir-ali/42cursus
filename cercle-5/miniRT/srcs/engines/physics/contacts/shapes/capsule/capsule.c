/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:38:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Finds the closest points between two line segments [p1,p2] and
 *        [p3,p4] using the Ericson segment-segment closest-point algorithm.
 *        Returns false if the segments are nearly parallel and degenerate,
 *        true otherwise. Writes closest points to *ca and *cb.
 */
static bool	closest_seg_seg(t_vec3 p1, t_vec3 p2, t_vec3 p3, t_vec3 p4,
							t_vec3 *ca, t_vec3 *cb)
{
	t_vec3	d1;
	t_vec3	d2;
	t_vec3	r;
	double	a;
	double	e;
	double	f;
	double	c;
	double	b;
	double	s;
	double	t;
	double	denom;

	d1 = vec3_sub(p2, p1);
	d2 = vec3_sub(p4, p3);
	r = vec3_sub(p1, p3);
	a = vec3_dot(d1, d1);
	e = vec3_dot(d2, d2);
	f = vec3_dot(d2, r);
	if (a < 1e-12 && e < 1e-12)
	{
		*ca = p1;
		*cb = p3;
		return (true);
	}
	if (a < 1e-12)
	{
		s = 0.0;
		t = clamp_d(f / e, 0.0, 1.0);
	}
	else
	{
		c = vec3_dot(d1, r);
		if (e < 1e-12)
		{
			t = 0.0;
			s = clamp_d(-c / a, 0.0, 1.0);
		}
		else
		{
			b = vec3_dot(d1, d2);
			denom = a * e - b * b;
			if (fabs(denom) > 1e-12)
				s = clamp_d((b * f - c * e) / denom, 0.0, 1.0);
			else
				s = 0.0;
			t = (b * s + f) / e;
			if (t < 0.0)
			{
				t = 0.0;
				s = clamp_d(-c / a, 0.0, 1.0);
			}
			else if (t > 1.0)
			{
				t = 1.0;
				s = clamp_d((b - c) / a, 0.0, 1.0);
			}
		}
	}
	*ca = vec3_add(p1, vec3_scale(d1, s));
	*cb = vec3_add(p3, vec3_scale(d2, t));
	return (true);
}

/**
 * @brief Analytic capsule-capsule contact generation.
 *        Avoids GJK+EPA for this pair — computes the exact contact point, 
 *        normal, and penetration depth from segment closest-point geometry.
 *        Produces a single, correctly-placed contact on the capsule surfaces.
 */
bool	analytic_capsule_capsule(t_contact_query *qu,
		t_capsule *a, t_capsule *b)
{
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	p3;
	t_vec3	p4;
	t_vec3	ca;
	t_vec3	cb;
	t_vec3	d;
	double	dist_sq;
	double	dist;
	double	sum_r;
	t_vec3	normal;
	t_contact	*c;

	p1 = vec3_sub(a->transform.pos, vec3_scale(a->axis, a->half_height));
	p2 = vec3_add(a->transform.pos, vec3_scale(a->axis, a->half_height));
	p3 = vec3_sub(b->transform.pos, vec3_scale(b->axis, b->half_height));
	p4 = vec3_add(b->transform.pos, vec3_scale(b->axis, b->half_height));
	closest_seg_seg(p1, p2, p3, p4, &ca, &cb);
	d = vec3_sub(ca, cb);
	dist_sq = vec3_dot(d, d);
	sum_r = a->radius + b->radius;
	if (dist_sq >= sum_r * sum_r)
		return (false);
	if (qu->count >= qu->max)
		return (false);
	dist = sqrt(dist_sq);
	if (dist > 1e-9)
		normal = vec3_scale(d, 1.0 / dist);
	else
	{
		normal = vec3_norm(vec3_cross(a->axis, b->axis));
		if (vec3_mag_sq(normal) < 1e-9)
		{
			normal = vec3(1, 0, 0);
			if (fabs(a->axis.x) > 0.9)
				normal = vec3(0, 1, 0);
		}
	}
	c = &qu->contacts[qu->count];
	c->normal = normal;
	c->penetration = sum_r - dist;
	c->a = &a->phys;
	c->b = &b->phys;
	c->ta = &a->transform;
	c->tb = &b->transform;
	c->contact_point = vec3_scale(
			vec3_add(vec3_sub(ca, vec3_scale(normal, a->radius)),
				vec3_add(cb, vec3_scale(normal, b->radius))), 0.5);
	c->ra = vec3_sub(c->contact_point, a->phys.center);
	c->rb = vec3_sub(c->contact_point, b->phys.center);
	c->lambda_pos = 0.0;
	c->restitution = fmin(a->phys.elasticity, b->phys.elasticity);
	c->friction = sqrt(a->phys.friction * b->phys.friction);
	qu->count++;
	return (true);
}
