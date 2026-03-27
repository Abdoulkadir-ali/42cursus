/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:48:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 16:48:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

bool	intersect_tri_shape(const t_ray *ray, t_tri_shape *tr, t_hit *hit)
{
	double	t;
	t_vec2	uv;

	if (!intersect_triangle_fast(ray, tr->v, &t, &uv))
		return (false);
	hit->t = t;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	hit->normal = vec3_cross(vec3_sub(tr->v[1], tr->v[0]),
			vec3_sub(tr->v[2], tr->v[0]));
	hit->normal = vec3_normalize(hit->normal);
	if (vec3_dot(ray->direction, hit->normal) > 0)
		hit->normal = vec3_scale(hit->normal, -1.0);
	hit->u = uv.x;
	hit->v = uv.y;
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
	return (true);
}
