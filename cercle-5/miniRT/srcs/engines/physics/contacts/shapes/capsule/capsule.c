/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 17:31:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	calc_st(t_seg_calc *sc, double *s, double *t)
{
	double	b;
	double	c;
	double	denom;

	c = vec3_dot(sc->d1, sc->r);
	if (sc->e < 1e-12)
	{
		*t = 0.0;
		*s = clamp_d(-c / sc->a, 0.0, 1.0);
		return ;
	}
	b = vec3_dot(sc->d1, sc->d2);
	denom = sc->a * sc->e - b * b;
	if (fabs(denom) > 1e-12)
		*s = clamp_d((b * sc->f - c * sc->e) / denom, 0.0, 1.0);
	else
		*s = 0.0;
	*t = (b * (*s) + sc->f) / sc->e;
	if (*t < 0.0)
		*s = clamp_d(-c / sc->a, 0.0, 1.0);
	else if (*t > 1.0)
		*s = clamp_d((b - c) / sc->a, 0.0, 1.0);
	*t = clamp_d(*t, 0.0, 1.0);
}

static bool	check_degenerate(t_vec3 p[4], t_vec3 *ca, t_vec3 *cb,
				struct s_seg_calc *sc)
{
	if (sc->a < 1e-12 && sc->e < 1e-12)
	{
		*ca = p[0];
		*cb = p[2];
		return (true);
	}
	if (sc->a < 1e-12)
	{
		*ca = p[0];
		*cb = vec3_add(p[2], vec3_scale(sc->d2, clamp_d(sc->f / sc->e,
						0.0, 1.0)));
		return (true);
	}
	return (false);
}

static bool	closest_seg_seg(t_vec3 p[4], t_vec3 *ca, t_vec3 *cb)
{
	struct s_seg_calc	sc;
	double				s;
	double				t;

	sc.d1 = vec3_sub(p[1], p[0]);
	sc.d2 = vec3_sub(p[3], p[2]);
	sc.r = vec3_sub(p[0], p[2]);
	sc.a = vec3_dot(sc.d1, sc.d1);
	sc.e = vec3_dot(sc.d2, sc.d2);
	sc.f = vec3_dot(sc.d2, sc.r);
	if (check_degenerate(p, ca, cb, &sc))
		return (true);
	calc_st(&sc, &s, &t);
	*ca = vec3_add(p[0], vec3_scale(sc.d1, s));
	*cb = vec3_add(p[2], vec3_scale(sc.d2, t));
	return (true);
}

static void	set_capsule_contact(t_contact_query *qu, t_capsule *a, t_capsule *b,
				t_vec3 c[2])
{
	t_contact	*co;
	t_vec3		normal;
	double		dist;

	normal = vec3_sub(c[0], c[1]);
	dist = vec3_mag(normal);
	if (dist > 1e-9)
		normal = vec3_scale(normal, 1.0 / dist);
	else
		normal = vec3_norm(vec3_cross(a->axis, b->axis));
	co = &qu->contacts[qu->count];
	co->normal = normal;
	co->penetration = a->radius + b->radius - dist;
	co->a = &a->phys;
	co->b = &b->phys;
	co->ta = &a->transform;
	co->tb = &b->transform;
	co->contact_point = vec3_scale(
			vec3_add(vec3_sub(c[0], vec3_scale(normal, a->radius)),
				vec3_add(c[1], vec3_scale(normal, b->radius))), 0.5);
	co->ra = vec3_sub(co->contact_point, a->phys.center);
	co->rb = vec3_sub(co->contact_point, b->phys.center);
	co->restitution = fmin(a->phys.elasticity, b->phys.elasticity);
	co->friction = sqrt(a->phys.friction * b->phys.friction);
	qu->count++;
}

bool	analytic_capsule_capsule(t_contact_query *qu,
		t_capsule *a, t_capsule *b)
{
	t_vec3	p[4];
	t_vec3	c[2];
	double	sum_r;

	p[0] = vec3_sub(a->transform.pos, vec3_scale(a->axis, a->half_height));
	p[1] = vec3_add(a->transform.pos, vec3_scale(a->axis, a->half_height));
	p[2] = vec3_sub(b->transform.pos, vec3_scale(b->axis, b->half_height));
	p[3] = vec3_add(b->transform.pos, vec3_scale(b->axis, b->half_height));
	closest_seg_seg(p, &c[0], &c[1]);
	sum_r = a->radius + b->radius;
	if (vec3_mag_sq(vec3_sub(c[0], c[1])) >= sum_r * sum_r
		|| qu->count >= qu->max)
		return (false);
	set_capsule_contact(qu, a, b, c);
	return (true);
}
