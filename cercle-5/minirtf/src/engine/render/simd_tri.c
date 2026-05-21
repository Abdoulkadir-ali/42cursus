/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simd_tri.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 23:28:39 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:51:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <immintrin.h>

/* Ray vs 4 triangles (SSE4.1) */
int	hit_triangle_sse(const t_tri_soa4 *t, const t_ray *r, t_hit *h)
{
	__m128	rdx, rdy, rdz, rox, roy, roz;
	__m128	e1x, e1y, e1z, e2x, e2y, e2z;
	__m128	ax, ay, az;
	__m128	pvx, pvy, pvz, det, inv_det;
	__m128	tvx, tvy, tvz, u, qvx, qvy, qvz, v, tt;
	__m128	mask, ht, eps;
	t_vec4	f_tt;
	t_vec4	f_u;
	t_vec4	f_v;
	int		m, i, hit_idx = -1;

	rdx = _mm_set1_ps(r->d.x); rdy = _mm_set1_ps(r->d.y); rdz = _mm_set1_ps(r->d.z);
	rox = _mm_set1_ps(r->o.x); roy = _mm_set1_ps(r->o.y); roz = _mm_set1_ps(r->o.z);
	e1x = _mm_loadu_ps(t->e1x.v); e1y = _mm_loadu_ps(t->e1y.v); e1z = _mm_loadu_ps(t->e1z.v);
	e2x = _mm_loadu_ps(t->e2x.v); e2y = _mm_loadu_ps(t->e2y.v); e2z = _mm_loadu_ps(t->e2z.v);
	ax = _mm_loadu_ps(t->ax.v); ay = _mm_loadu_ps(t->ay.v); az = _mm_loadu_ps(t->az.v);

	/* pv = r->d x e2 */
	pvx = _mm_sub_ps(_mm_mul_ps(rdy, e2z), _mm_mul_ps(rdz, e2y));
	pvy = _mm_sub_ps(_mm_mul_ps(rdz, e2x), _mm_mul_ps(rdx, e2z));
	pvz = _mm_sub_ps(_mm_mul_ps(rdx, e2y), _mm_mul_ps(rdy, e2x));

	/* det = e1 . pv */
	det = _mm_add_ps(_mm_mul_ps(e1x, pvx), _mm_add_ps(_mm_mul_ps(e1y, pvy), _mm_mul_ps(e1z, pvz)));
	mask = _mm_cmpgt_ps(_mm_and_ps(det, _mm_castsi128_ps(_mm_set1_epi32(0x7fffffff))), _mm_set1_ps(1e-10f));
	if (_mm_movemask_ps(mask) == 0) return (0);

	inv_det = _mm_div_ps(_mm_set1_ps(1.0f), det);
	tvx = _mm_sub_ps(rox, ax); tvy = _mm_sub_ps(roy, ay); tvz = _mm_sub_ps(roz, az);
	u = _mm_mul_ps(_mm_add_ps(_mm_mul_ps(tvx, pvx), _mm_add_ps(_mm_mul_ps(tvy, pvy), _mm_mul_ps(tvz, pvz))), inv_det);
	mask = _mm_and_ps(mask, _mm_and_ps(_mm_cmpge_ps(u, _mm_set1_ps(0.0f)), _mm_cmple_ps(u, _mm_set1_ps(1.0f))));
	if (_mm_movemask_ps(mask) == 0) return (0);

	/* qv = tv x e1 */
	qvx = _mm_sub_ps(_mm_mul_ps(tvy, e1z), _mm_mul_ps(tvz, e1y));
	qvy = _mm_sub_ps(_mm_mul_ps(tvz, e1x), _mm_mul_ps(tvx, e1z));
	qvz = _mm_sub_ps(_mm_mul_ps(tvx, e1y), _mm_mul_ps(tvy, e1x));

	v = _mm_mul_ps(_mm_add_ps(_mm_mul_ps(rdx, qvx), _mm_add_ps(_mm_mul_ps(rdy, qvy), _mm_mul_ps(rdz, qvz))), inv_det);
	mask = _mm_and_ps(mask, _mm_and_ps(_mm_cmpge_ps(v, _mm_set1_ps(0.0f)), _mm_cmple_ps(_mm_add_ps(u, v), _mm_set1_ps(1.0f))));
	if (_mm_movemask_ps(mask) == 0) return (0);

	tt = _mm_mul_ps(_mm_add_ps(_mm_mul_ps(e2x, qvx), _mm_add_ps(_mm_mul_ps(e2y, qvy), _mm_mul_ps(e2z, qvz))), inv_det);
	ht = _mm_set1_ps(h->t); eps = _mm_set1_ps(EPSILON);
	mask = _mm_and_ps(mask, _mm_and_ps(_mm_cmpgt_ps(tt, eps), _mm_cmplt_ps(tt, ht)));
	m = _mm_movemask_ps(mask);
	if (m == 0) return (0);

	_mm_storeu_ps(f_tt.v, tt); _mm_storeu_ps(f_u.v, u); _mm_storeu_ps(f_v.v, v);
	for (i = 0; i < 4; i++)
	{
		if ((m & (1 << i)) && f_tt.v[i] < h->t)
		{
			h->t = f_tt.v[i];
			hit_idx = i;
		}
	}
	if (hit_idx == -1) return (0);
	h->obj_index = t->ids[hit_idx];
	h->p = ray_at(*r, h->t);
	h->n = v3(t->nx.v[hit_idx], t->ny.v[hit_idx], t->nz.v[hit_idx]);
	if (v3_dot(h->n, r->d) > 0.0f) h->n = v3_neg(h->n);
	h->u = f_u.v[hit_idx];
	h->v = f_v.v[hit_idx];
	return (1);
}
