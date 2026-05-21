/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:11:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	hit_cylinder(const t_cylinder *c, const t_ray *r, t_hit *h)
{
	t_vec3	ca;
	t_vec3	oc;
	t_vec3	d;
	t_vec3	w;
	float	dv;
	float	w0v;
	float	a;
	float	b;
	float	c0;
	float	discr;
	float	t0;
	float	t1;
	float	best;
	t_vec3	p;
	t_vec3	n;
	float	y;

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
		return (0);
	discr = b * b - 4.0f * a * c0;
	if (discr < 0.0f)
		return (0);
	discr = sqrtf(discr);
	t0 = (-b - discr) / (2.0f * a);
	t1 = (-b + discr) / (2.0f * a);
	best = T_MAX;
	if (t0 > EPSILON)
	{
		y = w0v + dv * t0;
		if (y >= 0.0f && y <= c->height)
			best = t0;
	}
	if (t1 > EPSILON)
	{
		y = w0v + dv * t1;
		if (y >= 0.0f && y <= c->height && t1 < best)
			best = t1;
	}
	if (best >= h->t || best == T_MAX)
		return (0);
	h->t = best;
	h->p = ray_at(*r, best);
	p = v3_sub(h->p, c->base);
	n = v3_sub(p, v3_mul(ca, v3_dot(p, ca)));
	h->n = v3_norm(n);
	if (v3_dot(h->n, r->d) > 0.0f)
		h->n = v3_neg(h->n);
	return (1);
}
