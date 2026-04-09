/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:38:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Returns the furthest point of a rectangle along the search direction.
 *        A small skin offset in the face-normal direction is added to give
 *        GJK/EPA a non-degenerate slab to work with for this zero-thickness
 *        shape.  The same corner is used; only the normal extent is bumped.
 */
t_vec3	gjk_support_rect(const void *data, t_vec3 dir)
{
	const t_rect	*rc;
	t_vec3			best;
	double			best_d;
	size_t			i;

	rc = (const t_rect *)data;
	best = rc->v[0];
	best_d = vec3_dot(rc->v[0], dir);
	i = 1;
	while (i < 4)
	{
		if (vec3_dot(rc->v[i], dir) > best_d)
		{
			best_d = vec3_dot(rc->v[i], dir);
			best = rc->v[i];
		}
		i++;
	}
	if (vec3_dot(rc->normal, dir) >= 0.0)
		return (vec3_add(best, vec3_scale(rc->normal, PHYS_SKIN)));
	return (vec3_sub(best, vec3_scale(rc->normal, PHYS_SKIN)));
}
