/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 20:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief DOD-compliant GJK support point for a pyramid.
 * Calculates corners and apex dynamically from SoA data.
 */
t_vec3	gjk_support_pyramid(const t_gjk_shape *s, t_vec3 dir)
{
	t_primitive_array	*p;
	t_vec3				v[5];
	t_vec3				axis;
	t_vec3				basis[2];
	t_vec3				pos;

	p = &s->scene->primitives;
	pos = vec3(p->px[s->idx], p->py[s->idx], p->pz[s->idx]);
	axis = vec3(p->ax[s->idx], p->ay[s->idx], p->az[s->idx]);
	basis[0] = (fabs(axis.y) < 0.9) ? vec3(0, 1, 0) : vec3(1, 0, 0);
	basis[0] = vec3_norm(vec3_cross(axis, basis[0]));
	basis[1] = vec3_norm(vec3_cross(basis[0], axis));
	v[0] = vec3_add(vec3_add(pos, vec3_scale(basis[0], p->ex[s->idx])),
			vec3_scale(basis[1], p->ez[s->idx]));
	v[1] = vec3_add(vec3_add(pos, vec3_scale(basis[0], -p->ex[s->idx])),
			vec3_scale(basis[1], p->ez[s->idx]));
	v[2] = vec3_add(vec3_add(pos, vec3_scale(basis[0], -p->ex[s->idx])),
			vec3_scale(basis[1], -p->ez[s->idx]));
	v[3] = vec3_add(vec3_add(pos, vec3_scale(basis[0], p->ex[s->idx])),
			vec3_scale(basis[1], -p->ez[s->idx]));
	v[4] = vec3_add(pos, vec3_scale(axis, (double)p->heights[s->idx]));
	return (gjk_support_list(v, 5, dir));
}
