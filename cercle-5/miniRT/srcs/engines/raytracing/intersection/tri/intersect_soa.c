/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_soa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 02:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 08:46:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief DOD-compliant ray-triangle intersection using the SoA tri layout.
 * Optimized with the Möller-Trumbore algorithm and pre-computed world data.
 */
bool	intersect_tri_soa(const t_ray *r, t_tri_array *t, int i, t_hit *h)
{
	t_vec3	pvec;
	t_vec3	tvec;
	t_vec3	qvec;
	double	det;
	double	inv_det;
	double	u;
	double	v;

	pvec = vec3_cross(r->direction, vec3(t->ex[1][i], t->ey[1][i], t->ez[1][i]));
	det = vec3_dot(vec3(t->ex[0][i], t->ey[0][i], t->ez[0][i]), pvec);
	if (fabs(det) < EPSILON)
		return (false);
	inv_det = 1.0 / det;
	tvec = vec3_sub(r->origin, vec3(t->vx[0][i], t->vy[0][i], t->vz[0][i]));
	u = vec3_dot(tvec, pvec) * inv_det;
	if (u < 0.0 || u > 1.0)
		return (false);
	qvec = vec3_cross(tvec, vec3(t->ex[0][i], t->ey[0][i], t->ez[0][i]));
	v = vec3_dot(r->direction, qvec) * inv_det;
	if (v < 0.0 || u + v > 1.0)
		return (false);
	h->t = vec3_dot(vec3(t->ex[1][i], t->ey[1][i], t->ez[1][i]), qvec) * inv_det;
	if (h->t < EPSILON)
		return (false);
	h->normal = vec3(t->nx[i], t->ny[i], t->nz[i]);
	h->tangent = vec3(t->tx[i], t->ty[i], t->tz[i]);
	vec3_orthonormal_basis(h->normal, &h->tangent, &h->bitangent);
	h->point = vec3_add(r->origin, vec3_scale(r->direction, h->t));
	h->u = u; h->v = v;
	h->mat_idx = t->mat_ids[i];
	h->type = TYPE_TRI;
	return (true);
}
