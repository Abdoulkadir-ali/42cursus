/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:19:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief DOD-compliant GJK support point for a sphere.
 * Fetches position and radius directly from the primitive SoA.
 */
t_vec3	gjk_support_sphere(const t_gjk_shape *s, t_vec3 dir)
{
	t_sphere	sp;
	double		len;

	sp = unpack_sphere(&s->scene->primitives, s->idx);
	len = vec3_mag(dir);
	if (len < 1e-9)
		return (sp.center);
	return (vec3_add(sp.center, vec3_scale(dir, sp.radius / len)));
}
