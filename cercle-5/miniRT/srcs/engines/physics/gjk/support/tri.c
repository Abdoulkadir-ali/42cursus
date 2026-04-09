/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:38:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Returns the furthest point of a triangle along the search direction.
 *        A small skin offset in the face-normal direction is applied to give
 *        the zero-thickness triangle a non-degenerate slab for GJK/EPA.
 */
t_vec3	gjk_support_tri(const void *data, t_vec3 dir)
{
	const t_tri_shape	*tr;
	t_vec3				best;
	double				best_d;
	size_t				i;

	tr = (const t_tri_shape *)data;
	best = tr->v[0];
	best_d = vec3_dot(tr->v[0], dir);
	i = 1;
	while (i < 3)
	{
		if (vec3_dot(tr->v[i], dir) > best_d)
		{
			best_d = vec3_dot(tr->v[i], dir);
			best = tr->v[i];
		}
		i++;
	}
	if (vec3_dot(tr->normal, dir) >= 0.0)
		return (vec3_add(best, vec3_scale(tr->normal, PHYS_SKIN)));
	return (vec3_sub(best, vec3_scale(tr->normal, PHYS_SKIN)));
}
