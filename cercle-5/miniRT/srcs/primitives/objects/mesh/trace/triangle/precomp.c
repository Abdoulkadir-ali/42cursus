/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precomp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:11:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

static bool	tri_precomp_bary(const t_ray *ray, const t_tri_precomp *tc,
		t_tri_hit *hit)
{
	hit->pvec = vec3_cross(ray->direction, tc->e2);
	hit->det = vec3_dot(tc->e1, hit->pvec);
	if (hit->det > -1e-8 && hit->det < 1e-8)
		return (false);
	hit->inv_det = 1.0 / hit->det;
	hit->tvec = vec3_sub(ray->origin, tc->v0);
	hit->u = vec3_dot(hit->tvec, hit->pvec) * hit->inv_det;
	if (hit->u < 0.0 || hit->u > 1.0)
		return (false);
	hit->qvec = vec3_cross(hit->tvec, tc->e1);
	hit->v = vec3_dot(ray->direction, hit->qvec) * hit->inv_det;
	if (hit->v < 0.0 || hit->u + hit->v > 1.0)
		return (false);
	return (true);
}

/**
 * Perform a ray-triangle intersection test using precomputed triangle 
 * edge data for optimized performance during BVH traversal.
 */
bool	intersect_tri_precomp(const t_ray *ray, const t_tri_precomp *tc,
		double *t, t_vec2 *uv)
{
	t_tri_hit	hit;

	if (!tri_precomp_bary(ray, tc, &hit))
		return (false);
	*t = vec3_dot(tc->e2, hit.qvec) * hit.inv_det;
	if (*t <= EPSILON)
		return (false);
	if (uv)
	{
		uv->x = hit.u;
		uv->y = hit.v;
	}
	return (true);
}
