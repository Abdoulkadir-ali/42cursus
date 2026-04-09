/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:38:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Returns the furthest vertex of a pyramid along the search direction.
 *        Reads pre-cached vertices updated by integrate_pyramid() each frame,
 *        avoiding the cross-product vertex recomputation on every GJK/EPA call.
 */
t_vec3	gjk_support_pyramid(const void *data, t_vec3 dir)
{
	const t_pyramid	*py;
	t_vec3			best;
	double			best_d;
	double			d;
	int				i;

	py = (const t_pyramid *)data;
	best = py->c[0];
	best_d = vec3_dot(py->c[0], dir);
	i = 1;
	while (i < 4)
	{
		d = vec3_dot(py->c[i], dir);
		if (d > best_d)
		{
			best_d = d;
			best = py->c[i];
		}
		i++;
	}
	d = vec3_dot(py->apex, dir);
	if (d > best_d)
		best = py->apex;
	return (best);
}
