/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Returns the furthest vertex of a triangle along the search direction.
 */
t_vec3	gjk_support_tri(const void *data, t_vec3 dir)
{
	const t_tri_shape	*tr;
	t_vec3				best;
	double				best_d;
	double				d;
	size_t				i;

	tr = (const t_tri_shape *)data;
	best = tr->v[0];
	best_d = vec3_dot(tr->v[0], dir);
	i = 1;
	while (i < 3)
	{
		d = vec3_dot(tr->v[i], dir);
		if (d > best_d)
		{
			best_d = d;
			best = tr->v[i];
		}
		i++;
	}
	return (best);
}
