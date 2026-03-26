/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:08:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Constructs a triangular face for the EPA polytope.
 * Calculates the outward-pointing normal and its distance to the origin.
 */
t_epa_face	make_face(t_epa_poly *p, int i0, int i1, int i2)
{
	t_epa_face	f;
	t_vec3		e[2];
	t_vec3		n;
	double		len;

	f.idx[0] = i0;
	f.idx[1] = i1;
	f.idx[2] = i2;
	e[0] = vec3_sub(p->pts[i1], p->pts[i0]);
	e[1] = vec3_sub(p->pts[i2], p->pts[i0]);
	n = vec3_cross(e[0], e[1]);
	len = vec3_mag(n);
	if (len < 1e-12)
	{
		f.normal = vec3(0, 1, 0);
		f.dist = 0.0;
		return (f);
	}
	f.normal = vec3_scale(n, 1.0 / len);
	f.dist = vec3_dot(f.normal, p->pts[i0]);
	if (f.dist < 0.0)
	{
		f.normal = vec3_scale(f.normal, -1.0);
		f.dist = -f.dist;
	}
	return (f);
}

/**
 * @brief Computes barycentric coordinates (u, v, w) for point p on triangle (tri).
 */
t_vec3	bary(const t_vec3 tri[3], t_vec3 p)
{
	t_vec3	v[3];
	double	d[5];
	double	denom;
	double	vw[2];

	v[0] = vec3_sub(tri[1], tri[0]);
	v[1] = vec3_sub(tri[2], tri[0]);
	v[2] = vec3_sub(p, tri[0]);
	d[0] = vec3_dot(v[0], v[0]);
	d[1] = vec3_dot(v[0], v[1]);
	d[2] = vec3_dot(v[1], v[1]);
	d[3] = vec3_dot(v[2], v[0]);
	d[4] = vec3_dot(v[2], v[1]);
	denom = d[0] * d[2] - d[1] * d[1];
	if (fabs(denom) < 1e-12)
		return (vec3(0.333, 0.333, 0.334));
	vw[0] = (d[2] * d[3] - d[1] * d[4]) / denom;
	vw[1] = (d[0] * d[4] - d[1] * d[3]) / denom;
	return (vec3(1.0 - vw[0] - vw[1], vw[0], vw[1]));
}
