/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 20:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief DOD-compliant GJK support point for a cylinder.
 * Fetches axis, radius, and height directly from the primitive SoA.
 */
t_vec3	gjk_support_cylinder(const t_gjk_shape *s, t_vec3 dir)
{
	t_primitive_array	*p;
	t_vec3				pos;
	t_vec3				axis;
	t_vec3				lat;
	double				d[2];

	p = &s->scene->primitives;
	pos = vec3(p->px[s->idx], p->py[s->idx], p->pz[s->idx]);
	axis = vec3(p->ax[s->idx], p->ay[s->idx], p->az[s->idx]);
	d[0] = vec3_dot(axis, dir);
	lat = vec3_sub(dir, vec3_scale(axis, d[0]));
	d[1] = vec3_mag(lat);
	if (d[1] > 1e-9)
		lat = vec3_scale(lat, (double)p->radii[s->idx] / d[1]);
	else
		lat = vec3(0, 0, 0);
	if (d[0] >= 0.0)
		return (vec3_add(vec3_add(pos,
					vec3_scale(axis, (double)p->heights[s->idx] * 0.5)), lat));
	return (vec3_add(vec3_sub(pos,
				vec3_scale(axis, (double)p->heights[s->idx] * 0.5)), lat));
}
