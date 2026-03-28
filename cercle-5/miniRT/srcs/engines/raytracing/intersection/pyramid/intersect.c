/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:10:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	try_tri(const t_ray *r, t_vec3 a, t_vec3 b, t_vec3 c, double *best, t_hit *h)
{
	t_vec3	v[3] = {a, b, c};
	double	t;
	t_vec2	uv;
	if (intersect_triangle_fast(r, v, &t, &uv) && t < *best && t > EPSILON) {
		*best = t;
		h->t = t;
		h->point = vec3_add(r->origin, vec3_scale(r->direction, t));
		h->normal = vec3_norm(vec3_cross(vec3_sub(b, a), vec3_sub(c, a)));
		if (vec3_dot(r->direction, h->normal) > 0) h->normal = vec3_scale(h->normal, -1.0);
		h->u = uv.x; h->v = uv.y;
		return (true);
	}
	return (false);
}

bool	intersect_pyramid(const t_ray *ray, t_primitive_array *p, int i, t_hit *hit)
{
	t_pyramid pyr = unpack_pyramid(p, i);
	t_vec3	right, fwd, apex, v[4];
	double	sz, best = 1e30;
	bool	any = false;

	vec3_orthonormal_basis(pyr.up, &right, &fwd);
	sz = pyr.size * 0.5;
	
	v[0] = vec3_add(vec3_add(pyr.pos, vec3_scale(right, sz)), vec3_scale(fwd, sz));
	v[1] = vec3_add(vec3_add(pyr.pos, vec3_scale(right, -sz)), vec3_scale(fwd, sz));
	v[2] = vec3_add(vec3_add(pyr.pos, vec3_scale(right, -sz)), vec3_scale(fwd, -sz));
	v[3] = vec3_add(vec3_add(pyr.pos, vec3_scale(right, sz)), vec3_scale(fwd, -sz));
	apex = vec3_add(pyr.pos, vec3_scale(pyr.up, pyr.height));
	
	if (try_tri(ray, v[0], v[1], v[2], &best, hit)) any = true;
	if (try_tri(ray, v[0], v[2], v[3], &best, hit)) any = true;
	if (try_tri(ray, v[0], v[1], apex, &best, hit)) any = true;
	if (try_tri(ray, v[1], v[2], apex, &best, hit)) any = true;
	if (try_tri(ray, v[2], v[3], apex, &best, hit)) any = true;
	if (try_tri(ray, v[3], v[0], apex, &best, hit)) any = true;
	
	if (any) {
		hit->mat_idx = pyr.mat_idx;
		hit->type = TYPE_PYRAMID;
		vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
	}
	return (any);
}
