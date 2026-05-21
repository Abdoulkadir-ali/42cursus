/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:13:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static t_triangle	make_triangle(t_vec3 a, t_vec3 b, t_vec3 c)
{
	t_triangle	tri;

	tri.a = a;
	tri.b = b;
	tri.c = c;
	tri.n = v3_norm(v3_cross(v3_sub(b, a), v3_sub(c, a)));
	return (tri);
}

int	hit_pyramid(const t_pyramid *p, const t_ray *r, t_hit *h)
{
	t_hit	tmp;
	t_vec3	a[4];
	t_triangle	tri;
	float	s;

	tmp = *h;
	s = p->side * 0.5f;
	a[0] = v3_add(p->base, v3_add(v3_mul(p->u, -s), v3_mul(p->v, -s)));
	a[1] = v3_add(p->base, v3_add(v3_mul(p->u,  s), v3_mul(p->v, -s)));
	a[2] = v3_add(p->base, v3_add(v3_mul(p->u,  s), v3_mul(p->v,  s)));
	a[3] = v3_add(p->base, v3_add(v3_mul(p->u, -s), v3_mul(p->v,  s)));
	tri = make_triangle(p->apex, a[0], a[1]);
	hit_triangle(&tri, r, &tmp);
	tri = make_triangle(p->apex, a[1], a[2]);
	hit_triangle(&tri, r, &tmp);
	tri = make_triangle(p->apex, a[2], a[3]);
	hit_triangle(&tri, r, &tmp);
	tri = make_triangle(p->apex, a[3], a[0]);
	hit_triangle(&tri, r, &tmp);
	tri = make_triangle(a[0], a[2], a[1]);
	hit_triangle(&tri, r, &tmp);
	tri = make_triangle(a[0], a[3], a[2]);
	hit_triangle(&tri, r, &tmp);
	if (tmp.t < h->t)
	{
		*h = tmp;
		return (1);
	}
	return (0);
}
