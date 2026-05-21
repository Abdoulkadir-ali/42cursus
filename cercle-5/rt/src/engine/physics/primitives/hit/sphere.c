/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:10:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	hit_sphere(const t_sphere *s, const t_ray *r, t_hit *h)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discr;
	float	t0;
	float	t1;
	float	best;

	oc = v3_sub(r->o, s->center);
	a = v3_dot(r->d, r->d);
	b = 2.0f * v3_dot(oc, r->d);
	c = v3_dot(oc, oc) - s->radius2;
	discr = b * b - 4.0f * a * c;
	if (discr < 0.0f || a <= 0.0f)
		return (0);
	discr = sqrtf(discr);
	t0 = (-b - discr) / (2.0f * a);
	t1 = (-b + discr) / (2.0f * a);
	if (t0 > EPSILON)
		best = t0;
	else if (t1 > EPSILON)
		best = t1;
	else
		return (0);
	if (best >= h->t)
		return (0);
	h->t = best;
	h->p = ray_at(*r, best);
	h->n = v3_norm(v3_sub(h->p, s->center));
	return (1);
}
