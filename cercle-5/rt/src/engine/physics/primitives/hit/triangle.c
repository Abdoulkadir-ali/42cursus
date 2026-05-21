/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:13:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static int	hit_triangle_internal(const t_triangle *tri, const t_ray *r,
		t_hit *h)
{
	t_vec3	e1;
	t_vec3	e2;
	t_vec3	pvec;
	t_vec3	qvec;
	t_vec3	tvec;
	float		det;
	float		inv_det;
	float		u;
	float		v;
	float		t;

	e1 = v3_sub(tri->b, tri->a);
	e2 = v3_sub(tri->c, tri->a);
	pvec = v3_cross(r->d, e2);
	det = v3_dot(e1, pvec);
	if (fabsf(det) < EPSILON)
		return (0);
	inv_det = 1.0f / det;
	tvec = v3_sub(r->o, tri->a);
	u = v3_dot(tvec, pvec) * inv_det;
	if (u < 0.0f || u > 1.0f)
		return (0);
	qvec = v3_cross(tvec, e1);
	v = v3_dot(r->d, qvec) * inv_det;
	if (v < 0.0f || u + v > 1.0f)
		return (0);
	t = v3_dot(e2, qvec) * inv_det;
	if (t <= EPSILON || t >= h->t)
		return (0);
	h->t = t;
	h->p = ray_at(*r, t);
	h->n = v3_norm(tri->n);
	if (v3_dot(h->n, r->d) > 0.0f)
		h->n = v3_neg(h->n);
	return (1);
}

int	hit_triangle(const t_triangle *t, const t_ray *r, t_hit *h)
{
	return (hit_triangle_internal(t, r, h));
}


t_aabb	triangle_bounds(const t_triangle *t)
{
	t_aabb	b;

	b.min = t->a;
	b.max = t->a;
	b.min.x = fminf(b.min.x, t->b.x);
	b.min.y = fminf(b.min.y, t->b.y);
	b.min.z = fminf(b.min.z, t->b.z);
	b.max.x = fmaxf(b.max.x, t->b.x);
	b.max.y = fmaxf(b.max.y, t->b.y);
	b.max.z = fmaxf(b.max.z, t->b.z);
	b.min.x = fminf(b.min.x, t->c.x);
	b.min.y = fminf(b.min.y, t->c.y);
	b.min.z = fminf(b.min.z, t->c.z);
	b.max.x = fmaxf(b.max.x, t->c.x);
	b.max.y = fmaxf(b.max.y, t->c.y);
	b.max.z = fmaxf(b.max.z, t->c.z);
	return (b);
}

