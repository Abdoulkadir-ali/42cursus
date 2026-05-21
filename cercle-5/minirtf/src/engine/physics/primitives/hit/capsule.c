/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:13:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static float	closest_sphere_t(const t_vec3 center, float radius2,
		const t_ray *r)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discr;
	float	t0;
	float	t1;

	oc = v3_sub(r->o, center);
	a = v3_dot(r->d, r->d);
	b = 2.0f * v3_dot(oc, r->d);
	c = v3_dot(oc, oc) - radius2;
	discr = b * b - 4.0f * a * c;
	if (discr < 0.0f || a <= 0.0f)
		return (T_MAX);
	discr = sqrtf(discr);
	t0 = (-b - discr) / (2.0f * a);
	t1 = (-b + discr) / (2.0f * a);
	if (t0 > EPSILON)
		return (t0);
	if (t1 > EPSILON)
		return (t1);
	return (T_MAX);
}

static float	ray_capsule_axis_t(const t_capsule *c, const t_ray *r,
		float *best_t)
{
	t_vec3	ca;
	t_vec3	oc;
	float	dv;
	float	w0v;
	t_vec3	d;
	t_vec3	w;
	float	a;
	float	b;
	float	c0;
	float	discr;
	float	t0;
	float	t1;

	ca = c->axis;
	oc = v3_sub(r->o, c->base);
	dv = v3_dot(r->d, ca);
	w0v = v3_dot(oc, ca);
	d = v3_sub(r->d, v3_mul(ca, dv));
	w = v3_sub(oc, v3_mul(ca, w0v));
	a = v3_dot(d, d);
	b = 2.0f * v3_dot(d, w);
	c0 = v3_dot(w, w) - c->radius2;
	if (a <= 0.0f)
		return (T_MAX);
	discr = b * b - 4.0f * a * c0;
	if (discr < 0.0f)
		return (T_MAX);
	discr = sqrtf(discr);
	t0 = (-b - discr) / (2.0f * a);
	t1 = (-b + discr) / (2.0f * a);
	if (t0 > t1)
	{
		float	t;

		t = t0;
		t0 = t1;
		t1 = t;
	}
	if (t0 > EPSILON)
	{
		float	y;

		y = v3_dot(ca, v3_add(w, v3_mul(r->d, t0))) + w0v;
		if (y >= 0.0f && y <= c->height)
		{
			*best_t = t0;
			return (t0);
		}
	}
	if (t1 > EPSILON)
	{
		float	y;

		y = v3_dot(ca, v3_add(w, v3_mul(r->d, t1))) + w0v;
		if (y >= 0.0f && y <= c->height)
		{
			*best_t = t1;
			return (t1);
		}
	}
	return (T_MAX);
}

int	hit_capsule(const t_capsule *c, const t_ray *r, t_hit *h)
{
	t_vec3	p1;
	float	best;
	float	t;
	t_vec3	proj;

	p1 = v3_add(c->base, v3_mul(c->axis, c->height));
	best = T_MAX;
	t = closest_sphere_t(c->base, c->radius2, r);
	if (t > EPSILON && t < best)
		best = t;
	t = closest_sphere_t(p1, c->radius2, r);
	if (t > EPSILON && t < best)
		best = t;
	t = ray_capsule_axis_t(c, r, &best);
	if (best >= h->t || best == T_MAX)
		return (0);
	h->t = best;
	h->p = ray_at(*r, best);
	proj = v3_mul(c->axis, fmaxf(0.0f, fminf(c->height,
		v3_dot(v3_sub(h->p, c->base), c->axis))));
	h->n = v3_norm(v3_sub(h->p, v3_add(c->base, proj)));
	if (v3_dot(h->n, r->d) > 0.0f)
		h->n = v3_neg(h->n);
	return (1);
}
