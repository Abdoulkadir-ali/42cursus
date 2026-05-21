/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 18:26:37 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 18:26:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/* Ray vs 4 triangles (SSE4.1) - Vector Extensions Approach */
int	hit_triangle_sse(const t_tri_soa4 *t, const t_ray *r, t_hit *h)
{
	t_sv3	rd, ro, e1, e2, a, pv, tv, qv;
	t_v128	u, v, tt, det, idt;
	float	res[2];
	int		hit_idx;
	int		m;

	load_sse_tri(&rd, &ro, &e1, &e2, &a, t, r);
	pv = sv3_cross(rd, e2);
	det = sv3_dot(e1, pv);
	m = _mm_movemask_ps((__m128)(det > 1e-10f));
	if (m == 0)
		return (0);
	idt = 1.0f / det;
	tv = sv3_sub(ro, a);
	u = sv3_dot(tv, pv) * idt;
	m &= _mm_movemask_ps((__m128)((u >= 0.0f) & (u <= 1.0f)));
	if (m == 0)
		return (0);
	qv = sv3_cross(tv, e1);
	v = sv3_dot(rd, qv) * idt;
	m &= _mm_movemask_ps((__m128)((v >= 0.0f) & ((u + v) <= 1.0f)));
	if (m == 0)
		return (0);
	tt = sv3_dot(e2, qv) * idt;
	m &= _mm_movemask_ps((__m128)((tt > EPSILON) & (tt < h->t)));
	if (m == 0)
		return (0);
	hit_idx = find_best_hit(h, tt, u, v, m, res);
	if (hit_idx == -1)
		return (0);
	update_hit_sse(h, t, r, hit_idx, res[0], res[1]);
	return (1);
}
