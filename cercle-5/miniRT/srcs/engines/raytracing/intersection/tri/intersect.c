/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:48:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:10:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

bool	intersect_tri_soa(const t_ray *ray, t_tri_array *t, int i, t_hit *h)
{
	t_tri_view	tri = unpack_tri(t, i);
	t_vec3		edge1, edge2, pvec, tvec, qvec;
	double		det, inv_det, u, v, tt;

	edge1 = vec3_sub(tri.v1, tri.v0);
	edge2 = vec3_sub(tri.v2, tri.v0);
	pvec = vec3_cross(ray->direction, edge2);
	det = vec3_dot(edge1, pvec);
	if (fabs(det) < EPSILON)
		return (false);
	inv_det = 1.0 / det;
	tvec = vec3_sub(ray->origin, tri.v0);
	u = vec3_dot(tvec, pvec) * inv_det;
	if (u < 0.0 || u > 1.0)
		return (false);
	qvec = vec3_cross(tvec, edge1);
	v = vec3_dot(ray->direction, qvec) * inv_det;
	if (v < 0.0 || u + v > 1.0)
		return (false);
	tt = vec3_dot(edge2, qvec) * inv_det;
	if (tt < EPSILON)
		return (false);
	h->t = tt;
	h->point = vec3_add(ray->origin, vec3_scale(ray->direction, tt));
	h->normal = tri.n;
	if (vec3_dot(ray->direction, h->normal) > 0)
		h->normal = vec3_scale(h->normal, -1.0);
	h->u = u;
	h->v = v;
	h->mat_idx = tri.mat_idx;
	h->type = TYPE_TRI;
	vec3_orthonormal_basis(h->normal, &h->tangent, &h->bitangent);
	return (true);
}
