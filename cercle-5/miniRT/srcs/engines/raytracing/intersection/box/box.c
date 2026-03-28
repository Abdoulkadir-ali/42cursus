/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:10:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

bool	intersect_box(const t_ray *ray, t_primitive_array *p, int i, t_hit *hit)
{
	t_box bx = unpack_box(p, i);
	t_vec3 t_min, t_max;
	double min_t = -1e30, max_t = 1e30;

	t_vec3 inv_dir = vec3(1.0 / ray->direction.x, 1.0 / ray->direction.y, 1.0 / ray->direction.z);
	t_min = vec3_mul(vec3_sub(bx.min, ray->origin), inv_dir);
	t_max = vec3_mul(vec3_sub(bx.max, ray->origin), inv_dir);

	for (int axis = 0; axis < 3; axis++) {
		double v_min = (axis == 0 ? t_min.x : (axis == 1 ? t_min.y : t_min.z));
		double v_max = (axis == 0 ? t_max.x : (axis == 1 ? t_max.y : t_max.z));
		if (v_min > v_max) { double tmp = v_min; v_min = v_max; v_max = tmp; }
		if (v_min > min_t) min_t = v_min;
		if (v_max < max_t) max_t = v_max;
	}

	if (min_t > max_t || max_t < EPSILON) return (false);
	hit->t = (min_t > EPSILON) ? min_t : max_t;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	
	t_vec3 d = vec3_sub(hit->point, vec3_scale(vec3_add(bx.min, bx.max), 0.5));
	t_vec3 h = vec3_scale(vec3_sub(bx.max, bx.min), 0.5);
	hit->normal = vec3(0,0,0);
	if (fabs(d.x - h.x) < 0.001) hit->normal.x = 1;
	else if (fabs(d.x + h.x) < 0.001) hit->normal.x = -1;
	else if (fabs(d.y - h.y) < 0.001) hit->normal.y = 1;
	else if (fabs(d.y + h.y) < 0.001) hit->normal.y = -1;
	else if (fabs(d.z - h.z) < 0.001) hit->normal.z = 1;
	else if (fabs(d.z + h.z) < 0.001) hit->normal.z = -1;
	
	hit->mat_idx = bx.mat_idx;
	hit->type = TYPE_BOX;
	vec3_orthonormal_basis(hit->normal, &hit->tangent, &hit->bitangent);
	return (true);
}
