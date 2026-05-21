/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 18:26:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 18:26:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	load_sse_tri(t_sv3 *rd, t_sv3 *ro, t_sv3 *e1, t_sv3 *e2, t_sv3 *a, \
	const t_tri_soa4 *t, const t_ray *r)
{
	rd->x = (t_v128)_mm_set1_ps(r->d.x);
	rd->y = (t_v128)_mm_set1_ps(r->d.y);
	rd->z = (t_v128)_mm_set1_ps(r->d.z);
	ro->x = (t_v128)_mm_set1_ps(r->o.x);
	ro->y = (t_v128)_mm_set1_ps(r->o.y);
	ro->z = (t_v128)_mm_set1_ps(r->o.z);
	e1->x = (t_v128)_mm_loadu_ps(t->e1x.v);
	e1->y = (t_v128)_mm_loadu_ps(t->e1y.v);
	e1->z = (t_v128)_mm_loadu_ps(t->e1z.v);
	e2->x = (t_v128)_mm_loadu_ps(t->e2x.v);
	e2->y = (t_v128)_mm_loadu_ps(t->e2y.v);
	e2->z = (t_v128)_mm_loadu_ps(t->e2z.v);
	a->x = (t_v128)_mm_loadu_ps(t->ax.v);
	a->y = (t_v128)_mm_loadu_ps(t->ay.v);
	a->z = (t_v128)_mm_loadu_ps(t->az.v);
}

int	find_best_hit(t_hit *h, t_v128 tt, t_v128 u, t_v128 v, \
	int m, float res[2])
{
	t_vec4	f[3];
	int		i;
	int		hit_idx;

	_mm_storeu_ps(f[0].v, (__m128)tt);
	_mm_storeu_ps(f[1].v, (__m128)u);
	_mm_storeu_ps(f[2].v, (__m128)v);
	hit_idx = -1;
	i = -1;
	while (++i < 4)
	{
		if ((m & (1 << i)) && f[0].v[i] < h->t)
		{
			h->t = f[0].v[i];
			hit_idx = i;
		}
	}
	if (hit_idx != -1)
	{
		res[0] = f[1].v[hit_idx];
		res[1] = f[2].v[hit_idx];
	}
	return (hit_idx);
}

void	update_hit_sse(t_hit *h, const t_tri_soa4 *t, const t_ray *r, \
	int idx, float u, float v)
{
	h->obj_index = t->ids[idx];
	h->p = ray_at(*r, h->t);
	h->n = v3(t->nx.v[idx], t->ny.v[idx], t->nz.v[idx]);
	if (v3_dot(h->n, r->d) > 0.0f)
		h->n = v3_neg(h->n);
	h->u = u;
	h->v = v;
}
