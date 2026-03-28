/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 10:55:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 10:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief Möller-Trumbore intersection algorithm for a 3-vertex triangle.
 * Used as a utility by compound primitives (rect, pyramid).
 */
bool	intersect_triangle_fast(const t_ray *ray, t_vec3 v[3], double *t_out,
		t_vec2 *uv_out)
{
	t_vec3	e1, e2, pvec, tvec, qvec;
	double	det, inv_det, u, v_val;

	e1 = vec3_sub(v[1], v[0]);
	e2 = vec3_sub(v[2], v[0]);
	pvec = vec3_cross(ray->direction, e2);
	det = vec3_dot(e1, pvec);
	if (fabs(det) < EPSILON)
		return (false);
	inv_det = 1.0 / det;
	tvec = vec3_sub(ray->origin, v[0]);
	u = vec3_dot(tvec, pvec) * inv_det;
	if (u < 0.0 || u > 1.0)
		return (false);
	qvec = vec3_cross(tvec, e1);
	v_val = vec3_dot(ray->direction, qvec) * inv_det;
	if (v_val < 0.0 || u + v_val > 1.0)
		return (false);
	*t_out = vec3_dot(e2, qvec) * inv_det;
	if (*t_out < EPSILON)
		return (false);
	if (uv_out) { uv_out->x = u; uv_out->y = v_val; }
	return (true);
}
