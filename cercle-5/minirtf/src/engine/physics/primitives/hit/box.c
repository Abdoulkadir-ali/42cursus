/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:11:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static float	box_axis_t(const t_vec3 axis, float extent,
		const t_box *b, const t_ray *r, float *tmin, float *tmax)
{
	float	od;
	float	dd;
	float	t1;
	float	t2;

	od = v3_dot(axis, v3_sub(b->center, r->o));
	dd = v3_dot(axis, r->d);
	if (fabsf(dd) < EPSILON)
	{
		if (fabsf(od) > extent)
			return (0);
		return (1);
	}
	t1 = (od + extent) / dd;
	t2 = (od - extent) / dd;
	if (t1 > t2)
	{
		float	t;

		t = t1;
		t1 = t2;
		t2 = t;
	}
	if (t1 > *tmin)
		*tmin = t1;
	if (t2 < *tmax)
		*tmax = t2;
	return (*tmin <= *tmax);
}

static t_vec3	normal_for_box(const t_box *b, const t_vec3 point)
{
	float	x;
	float	y;
	float	z;
	t_vec3	d;

	d = v3_sub(point, b->center);
	x = fabsf(v3_dot(d, b->u));
	y = fabsf(v3_dot(d, b->v));
	z = fabsf(v3_dot(d, b->w));
	if (x > y && x > z)
	{
		if (v3_dot(d, b->u) > 0.0f)
			return (b->u);
		return (v3_neg(b->u));
	}
	if (y > z)
	{
		if (v3_dot(d, b->v) > 0.0f)
			return (b->v);
		return (v3_neg(b->v));
	}
	if (v3_dot(d, b->w) > 0.0f)
		return (b->w);
	return (v3_neg(b->w));
}

static float	ray_box_t(const t_box *b, const t_ray *r, t_hit *h)
{
	float	tmin;
	float	tmax;
	float	best;

	tmin = -T_MAX;
	tmax = T_MAX;
	if (!box_axis_t(b->u, b->he.x, b, r, &tmin, &tmax))
		return (T_MAX);
	if (!box_axis_t(b->v, b->he.y, b, r, &tmin, &tmax))
		return (T_MAX);
	if (!box_axis_t(b->w, b->he.z, b, r, &tmin, &tmax))
		return (T_MAX);
	best = tmin > EPSILON ? tmin : tmax > EPSILON ? tmax : T_MAX;
	if (best >= h->t)
		return (T_MAX);
	return (best);
}

int	hit_box(const t_box *b, const t_ray *r, t_hit *h)
{
	float	best;

	best = ray_box_t(b, r, h);
	if (best >= h->t || best == T_MAX)
		return (0);
	h->t = best;
	h->p = ray_at(*r, best);
	h->n = normal_for_box(b, h->p);
	return (1);
}
