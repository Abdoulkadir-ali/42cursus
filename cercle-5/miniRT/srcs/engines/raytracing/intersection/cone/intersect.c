/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:09:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	check_cone_height(const t_ray *ray, double t, t_cone co, double *h_out)
{
	t_vec3	pt;

	pt = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	*h_out = vec3_dot(vec3_sub(pt, co.tip), co.axis);
	if (*h_out < 0.0 || *h_out > co.height)
		return (false);
	return (true);
}

bool	intersect_cone(const t_ray *ray, t_primitive_array *p, int i, t_hit *hit)
{
	t_cone		co = unpack_cone(p, i);
	t_vec3		oc;
	double		k, a, b, c, delta, t1, t2, h;
	
	oc = vec3_sub(ray->origin, co.tip);
	/* co.angle is the base radius in this context */
	k = co.angle / co.height;
	k = k * k;
	
	a = vec3_dot(ray->direction, ray->direction) - (1 + k) * pow(vec3_dot(ray->direction, co.axis), 2);
	b = 2.0 * (vec3_dot(ray->direction, oc) - (1 + k) * vec3_dot(ray->direction, co.axis) * vec3_dot(oc, co.axis));
	c = vec3_dot(oc, oc) - (1 + k) * pow(vec3_dot(oc, co.axis), 2);
	
	delta = b * b - 4 * a * c;
	if (delta < 0) return (false);
	
	t1 = (-b - sqrt(delta)) / (2.0 * a);
	t2 = (-b + sqrt(delta)) / (2.0 * a);
	
	hit->t = -1.0;
	if (t1 > EPSILON && check_cone_height(ray, t1, co, &h))
		hit->t = t1;
	else if (t2 > EPSILON && check_cone_height(ray, t2, co, &h))
		hit->t = t2;
	else
		return (false);
		
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	t_vec3 radial = vec3_sub(vec3_sub(hit->point, co.tip), vec3_scale(co.axis, h));
	hit->normal = vec3_norm(vec3_sub(vec3_scale(radial, 1.0/sqrt(k)), vec3_scale(co.axis, sqrt(k))));
	if (vec3_dot(ray->direction, hit->normal) > 0)
		hit->normal = vec3_scale(hit->normal, -1.0);
	
	get_cone_uv(hit, p, i, radial, h);
	hit->mat_idx = co.mat_idx;
	hit->type = TYPE_CONE;
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
	return (true);
}
