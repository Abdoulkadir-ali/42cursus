/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:08:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

bool	intersect_plane(const t_ray *ray, t_primitive_array *p, int i, t_hit *hit)
{
	t_plane pl = unpack_plane(p, i);
	double	denom;
	double	t;

	denom = vec3_dot(pl.normal, ray->direction);
	if (fabs(denom) < EPSILON)
		return (false);
	t = vec3_dot(vec3_sub(pl.point, ray->origin), pl.normal) / denom;
	if (t < EPSILON)
		return (false);
	hit->t = t;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	hit->normal = pl.normal;
	if (denom > 0)
		hit->normal = vec3_scale(pl.normal, -1.0);
	get_plane_uv(hit->point, hit->normal, hit);
	hit->mat_idx = pl.mat_idx;
	hit->type = TYPE_PLANE;
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
	return (true);
}
