/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Returns the furthest corner of a rectangle along the search direction.
 */
t_vec3	gjk_support_rect(const void *data, t_vec3 dir)
{
	const t_rect	*rc;
	t_vec3			best;
	double			best_d;
	double			d;
	size_t			i;

	rc = (const t_rect *)data;
	best = rc->v[0];
	best_d = vec3_dot(rc->v[0], dir);
	i = 1;
	while (i < 4)
	{
		d = vec3_dot(rc->v[i], dir);
		if (d > best_d)
		{
			best_d = d;
			best = rc->v[i];
		}
		i++;
	}
	return (best);
}
