/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 12:47:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

bool	intersect_rect(const t_ray *ray, t_primitive_array *p, int i, t_hit *hit)
{
	t_rect re = unpack_rect(p, i);
	t_vec3	v, right, up, rel;
	double	denom, t, d_u, d_v;

	denom = vec3_dot(re.normal, ray->direction);
	if (fabs(denom) < EPSILON) return (false);
	
	t = vec3_dot(vec3_sub(re.pos, ray->origin), re.normal) / denom;
	if (t < EPSILON) return (false);
	
	v = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	rel = vec3_sub(v, re.pos);
	
	vec3_orthonormal_basis(re.normal, &right, &up);
	d_u = vec3_dot(rel, right);
	d_v = vec3_dot(rel, up);
	
	if (fabs(d_u) > re.ex || fabs(d_v) > re.ey)
		return (false);
		
	hit->t = t;
	hit->point = v;
	hit->normal = re.normal;
	if (denom > 0)
		hit->normal = vec3_scale(re.normal, -1.0);
	hit->u = (d_u / re.ex + 1.0) * 0.5;
	hit->v = (d_v / re.ey + 1.0) * 0.5;
	hit->mat_idx = re.mat_idx;
	hit->type = TYPE_RECT;
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
	return (true);
}
