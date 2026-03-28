/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:20:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief DOD-compliant GJK support point for a capsule.
 * Derived from center, axis, height, and radius in SoA storage.
 */
t_vec3	gjk_support_capsule(const t_gjk_shape *s, t_vec3 dir)
{
	t_capsule	cap;
	t_vec3		pole;
	double		len;

	cap = unpack_capsule(&s->scene->primitives, s->idx);
	if (vec3_dot(vec3_norm(vec3_sub(cap.b, cap.a)), dir) >= 0.0)
		pole = cap.b;
	else
		pole = cap.a;
	len = vec3_mag(dir);
	if (len < 1e-9)
		return (pole);
	return (vec3_add(pole, vec3_scale(dir, cap.radius / len)));
}
