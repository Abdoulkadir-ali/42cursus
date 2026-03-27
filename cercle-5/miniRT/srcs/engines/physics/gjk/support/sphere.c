/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Created: 2026/03/28 20:00:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief DOD-compliant GJK support point for a sphere.
 * Fetches position and radius directly from the primitive SoA.
 */
t_vec3	gjk_support_sphere(const t_gjk_shape *s, t_vec3 dir)
{
	t_primitive_array	*p;
	t_vec3				pos;
	double				len;

	p = &s->scene->primitives;
	pos = vec3(p->px[s->idx], p->py[s->idx], p->pz[s->idx]);
	len = vec3_mag(dir);
	if (len < 1e-9)
		return (pos);
	return (vec3_add(pos, vec3_scale(dir, (double)p->radii[s->idx] / len)));
}
