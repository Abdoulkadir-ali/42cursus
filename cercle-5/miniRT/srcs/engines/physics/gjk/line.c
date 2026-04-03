/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Identifies the search direction from a line segment toward the origin.
 */
static void	get_line_dir(t_vec3 a, t_vec3 b, t_vec3 *dir)
{
	t_vec3	ab;
	t_vec3	ao;

	ab = vec3_sub(b, a);
	ao = vec3_scale(a, -1.0);
	*dir = vec3_sub(vec3_scale(ao, vec3_dot(ab, ab)),
			vec3_scale(ab, vec3_dot(ao, ab)));
	if (vec3_mag_sq(*dir) < 1e-12)
		*dir = vec3_cross(ab, vec3(0, 1, 0));
	if (vec3_mag_sq(*dir) < 1e-12)
		*dir = vec3_cross(ab, vec3(1, 0, 0));
}

/**
 * @brief Handles the line-simplex case. Finds search direction toward origin.
 */
bool	gjk_simplex_line(t_simplex *s, t_vec3 *dir)
{
	t_vec3	a;
	t_vec3	b;

	a = s->pts[1];
	b = s->pts[0];
	if (vec3_dot(vec3_sub(b, a), vec3_scale(a, -1.0)) > 0.0)
		get_line_dir(a, b, dir);
	else
	{
		s->pts[0] = a;
		s->a_pts[0] = s->a_pts[1];
		s->b_pts[0] = s->b_pts[1];
		s->n = 1;
		*dir = vec3_scale(a, -1.0);
	}
	return (false);
}
