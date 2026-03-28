/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:20:16 by abdoali          ###   ########.fr       */
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
 * Uses extents (ex, ey,
	ez) to compute the furthest point in the given direction.
 */
t_vec3	gjk_support_box(const t_gjk_shape *s, t_vec3 dir)
{
	t_box	box;
	t_vec3	ext;
	t_vec3	center;

	box = unpack_box(&s->scene->primitives, s->idx);
	center = vec3_scale(vec3_add(box.min, box.max), 0.5);
	ext = vec3_scale(vec3_sub(box.max, box.min), 0.5);
	return (vec3_add(center, vec3(sign(dir.x) * ext.x, sign(dir.y) * ext.y,
				sign(dir.z) * ext.z)));
}
