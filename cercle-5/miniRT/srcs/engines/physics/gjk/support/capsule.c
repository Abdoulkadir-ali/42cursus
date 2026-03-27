/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 20:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief DOD-compliant GJK support point for a capsule.
 * Derived from center, axis, height, and radius in SoA storage.
 */
t_vec3	gjk_support_capsule(const t_gjk_shape *s, t_vec3 dir)
{
	t_primitive_array	*p;
	t_vec3				pos;
	t_vec3				axis;
	t_vec3				pole;
	double				len;

	p = &s->scene->primitives;
	pos = vec3(p->px[s->idx], p->py[s->idx], p->pz[s->idx]);
	axis = vec3(p->ax[s->idx], p->ay[s->idx], p->az[s->idx]);
	if (vec3_dot(axis, dir) >= 0.0)
		pole = vec3_add(pos, vec3_scale(axis, (double)p->heights[s->idx] / 2.0));
	else
		pole = vec3_sub(pos, vec3_scale(axis, (double)p->heights[s->idx] / 2.0));
	len = vec3_mag(dir);
	if (len < 1e-9)
		return (pole);
	return (vec3_add(pole, vec3_scale(dir, (double)p->radii[s->idx] / len)));
}
