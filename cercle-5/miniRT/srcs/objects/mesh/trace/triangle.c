/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_trace_triangle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static bool	tri_compute_bary(const t_ray *ray, t_vec3 v[3], t_tri_hit *hit)
{
	hit->e1 = vec3_sub(v[1], v[0]);
	hit->e2 = vec3_sub(v[2], v[0]);
	hit->pvec = vec3_cross(ray->direction, hit->e2);
	hit->det = vec3_dot(hit->e1, hit->pvec);
	if (fabs(hit->det) < 1e-8)
		return (false);
	hit->inv_det = 1.0 / hit->det;
	hit->tvec = vec3_sub(ray->origin, v[0]);
	hit->u = vec3_dot(hit->tvec, hit->pvec) * hit->inv_det;
	if (hit->u < 0.0 || hit->u > 1.0)
		return (false);
	hit->qvec = vec3_cross(hit->tvec, hit->e1);
	hit->v = vec3_dot(ray->direction, hit->qvec) * hit->inv_det;
	if (hit->v < 0.0 || hit->u + hit->v > 1.0)
		return (false);
	return (true);
}

static void	tri_set_uv(t_vec2 *uv, t_tri_hit *hit)
{
	uv->x = hit->u;
	uv->y = hit->v;
}

bool	intersect_triangle_fast(const t_ray *ray, t_vec3 v[3], double *t,
		t_vec2 *uv)
{
	t_tri_hit	hit;

	if (!tri_compute_bary(ray, v, &hit))
		return (false);
	*t = vec3_dot(hit.e2, hit.qvec) * hit.inv_det;
	if (*t <= EPSILON)
		return (false);
	if (uv)
		tri_set_uv(uv, &hit);
	return (true);
}
