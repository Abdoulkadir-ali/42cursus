/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:05:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void	compute_ab_ao(t_simplex *s, t_vec3 *ab, t_vec3 *ao)
{
	*ab = vec3_sub(s->pts[0], s->pts[1]);
	*ao = vec3_scale(s->pts[1], -1.0);
}

bool	handle_positive_simplex_line(t_vec3 ab, t_vec3 ao, t_vec3 *dir)
{
	t_vec3	axis;

	*dir = vec3_triple_product(ab, ao, ab);
	if (vec3_mag_sq(*dir) < 1e-12)
	{
		if (fabs(ab.x) < 0.9)
			axis = vec3(1, 0, 0);
		else
			axis = vec3(0, 1, 0);
		*dir = vec3_cross(ab, axis);
	}
	return (true);
}

void	reduce_simplex_to_point(t_simplex *s, t_vec3 ao, t_vec3 *dir)
{
	s->pts[0] = s->pts[1];
	s->a_pts[0] = s->a_pts[1];
	s->b_pts[0] = s->b_pts[1];
	s->n = 1;
	*dir = ao;
}

/**
 * @brief Handles GJK case for a 2-point simplex (line).
 * Searches for a new direction that moves toward the origin.
 */
bool	simplex_line(t_simplex *s, t_vec3 *dir)
{
	t_vec3	ab;
	t_vec3	ao;

	compute_ab_ao(s, &ab, &ao);
	if (vec3_dot(ab, ao) > 0.0)
		handle_positive_simplex_line(ab, ao, dir);
	else
		reduce_simplex_to_point(s, ao, dir);
	return (false);
}