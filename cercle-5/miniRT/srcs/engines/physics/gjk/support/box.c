/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 20:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static double	sign(double x)
{
	if (x < 0.0)
		return (-1.0);
	return (1.0);
}

/**
 * @brief GJK support point for a box in SoA storage.
 * Uses extents (ex, ey, ez) to compute the furthest point in the given direction.
 */
t_vec3	gjk_support_box(const t_gjk_shape *s, t_vec3 dir)
{
	t_primitive_array	*p;
	t_vec3				pos;
	t_vec3				ex;

	p = &s->scene->primitives;
	pos = vec3(p->px[s->idx], p->py[s->idx], p->pz[s->idx]);
	ex = vec3(p->ex[s->idx], p->ey[s->idx], p->ez[s->idx]);
	return (vec3_add(pos, vec3(sign(dir.x) * ex.x,
				sign(dir.y) * ex.y,
				sign(dir.z) * ex.z)));
}
