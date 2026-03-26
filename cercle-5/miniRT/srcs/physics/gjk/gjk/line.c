/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Handles GJK case for a 2-point simplex (line).
 * Searches for a new direction that moves toward the origin.
 */
bool	simplex_line(t_simplex *s, t_vec3 *dir)
{
	t_vec3	ab;
	t_vec3	ao;

	ab = vec3_sub(s->pts[0], s->pts[1]);
	ao = vec3_scale(s->pts[1], -1.0);
	if (vec3_dot(ab, ao) > 0.0)
	{
		*dir = vec3_triple_product(ab, ao, ab);
		if (vec3_mag_sq(*dir) < 1e-12)
			*dir = vec3_cross(ab, (fabs(ab.x) < 0.9) ? vec3(1, 0, 0)
					: vec3(0, 1, 0));
	}
	else
	{
		s->pts[0] = s->pts[1];
		s->a_pts[0] = s->a_pts[1];
		s->b_pts[0] = s->b_pts[1];
		s->n = 1;
		*dir = ao;
	}
	return (false);
}
