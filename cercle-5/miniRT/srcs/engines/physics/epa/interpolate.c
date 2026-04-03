/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 10:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Computes barycentric coordinates of point p relative to a triangle.
 */
static t_vec3	bary(t_vec3 a, t_vec3 b, t_vec3 c, t_vec3 p_pt)
{
	t_vec3	v[3];
	double	d[5];
	double	denom;
	double	v_w[2];

	v[0] = vec3_sub(b, a);
	v[1] = vec3_sub(c, a);
	v[2] = vec3_sub(p_pt, a);
	d[0] = vec3_dot(v[0], v[0]);
	d[1] = vec3_dot(v[0], v[1]);
	d[2] = vec3_dot(v[1], v[1]);
	d[3] = vec3_dot(v[2], v[0]);
	d[4] = vec3_dot(v[2], v[1]);
	denom = d[0] * d[2] - d[1] * d[1];
	if (fabs(denom) < 1e-12)
		return (vec3(0.333, 0.333, 0.334));
	v_w[0] = (d[2] * d[3] - d[1] * d[4]) / denom;
	v_w[1] = (d[0] * d[4] - d[1] * d[3]) / denom;
	return (vec3(1.0 - v_w[0] - v_w[1], v_w[0], v_w[1]));
}

/**
 * @brief Interpolates local contact points based on barycentric weights.
 */
void	epa_interpolate(t_epa_poly *poly, t_epa_face *f, t_epa_res *res)
{
	t_vec3	w;

	w = bary(poly->pts[f->idx[0]], poly->pts[f->idx[1]],
			poly->pts[f->idx[2]], vec3_scale(f->normal, f->dist));
	res->contact_a = vec3_add(vec3_add(
				vec3_scale(poly->a_pts[f->idx[0]], w.x),
				vec3_scale(poly->a_pts[f->idx[1]], w.y)),
			vec3_scale(poly->a_pts[f->idx[2]], w.z));
	res->contact_b = vec3_add(vec3_add(
				vec3_scale(poly->b_pts[f->idx[0]], w.x),
				vec3_scale(poly->b_pts[f->idx[1]], w.y)),
			vec3_scale(poly->b_pts[f->idx[2]], w.z));
	res->normal = f->normal;
	res->depth = f->dist;
}
