/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 08:46:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	check_cone_height(const t_ray *ray, double t, t_vec3 tip,
		t_vec3 axis, double height, double *h_out)
{
	t_vec3	pt;

	pt = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	*h_out = vec3_dot(vec3_sub(pt, tip), axis);
	if (*h_out < 0.0 || *h_out > height)
		return (false);
	return (true);
}

bool	intersect_cone(const t_ray *ray, t_primitive_array *p, int i, t_hit *hit)
{
	t_vec3		tip = vec3(p->px[i], p->py[i], p->pz[i]);
	t_vec3		axis = vec3(p->ax[i], p->ay[i], p->az[i]);
	double		radius = p->radii[i];
	double		height = p->heights[i];
	int			mat_idx = p->mat_ids[i];
	t_vec3		oc;
	double		k, a, b, c, delta, t1, t2, h;
	double		sqrt_delta;
	
	oc = vec3_sub(ray->origin, tip);
	k = radius / height;
	k = k * k;
	
	a = vec3_dot(ray->direction, ray->direction) - (1 + k) * (vec3_dot(ray->direction, axis) * vec3_dot(ray->direction, axis));
	b = 2.0 * (vec3_dot(ray->direction, oc) - (1 + k) * vec3_dot(ray->direction, axis) * vec3_dot(oc, axis));
	c = vec3_dot(oc, oc) - (1 + k) * (vec3_dot(oc, axis) * vec3_dot(oc, axis));
	
	delta = b * b - 4 * a * c;
	if (delta < 0) return (false);
	sqrt_delta = sqrt(delta);
	t1 = (-b - sqrt_delta) / (2.0 * a);
	t2 = (-b + sqrt_delta) / (2.0 * a);
	
	hit->t = -1.0;
	if (t1 > EPSILON && check_cone_height(ray, t1, tip, axis, height, &h))
		hit->t = t1;
	else if (t2 > EPSILON && check_cone_height(ray, t2, tip, axis, height, &h))
		hit->t = t2;
	else
		return (false);
		
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	t_vec3	radial = vec3_sub(vec3_sub(hit->point, tip), vec3_scale(axis, h));
	double	sqrt_k;
	double	inv_sqrt_k;

	sqrt_k = sqrt(k);
	inv_sqrt_k = 1.0 / sqrt_k;
	hit->normal = vec3_norm(vec3_sub(vec3_scale(radial, inv_sqrt_k), vec3_scale(axis, sqrt_k)));
	if (vec3_dot(ray->direction, hit->normal) > 0)
		hit->normal = vec3_scale(hit->normal, -1.0);
	
	get_cone_uv(hit, p, i, radial, h);
	hit->mat_idx = mat_idx;
	hit->type = TYPE_CONE;
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
	return (true);
}
