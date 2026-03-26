/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Generic support function for a list of vertices.
 * Returns the point furthest along the given direction.
 */
t_vec3	gjk_support_list(const t_vec3 *v, int n, t_vec3 dir)
{
	t_vec3	best;
	double	best_d;
	double	d;
	int		i;

	best = v[0];
	best_d = vec3_dot(v[0], dir);
	i = 0;
	while (++i < n)
	{
		d = vec3_dot(v[i], dir);
		if (d > best_d)
		{
			best_d = d;
			best = v[i];
		}
	}
	return (best);
}
