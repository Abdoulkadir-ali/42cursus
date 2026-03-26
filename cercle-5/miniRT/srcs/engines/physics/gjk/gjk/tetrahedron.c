/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrahedron.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Handles GJK case for a 4th order simplex (tetrahedron).
 * Investigates each of the four triangular faces for potential exits.
 */
bool	simplex_tetrahedron(t_simplex *s, t_vec3 *dir)
{
	t_vec3	ao;
	t_vec3	ab;
	t_vec3	ac;
	t_vec3	ad;

	ab = vec3_sub(s->pts[2], s->pts[3]);
	ac = vec3_sub(s->pts[1], s->pts[3]);
	ad = vec3_sub(s->pts[0], s->pts[3]);
	ao = vec3_scale(s->pts[3], -1.0);
	if (vec3_dot(vec3_cross(ab, ac), ao) > 0.0)
	{
		update_simplex3(s, 1, 2, 3);
		return (simplex_triangle(s, dir));
	}
	if (vec3_dot(vec3_cross(ac, ad), ao) > 0.0)
	{
		update_simplex3(s, 0, 1, 3);
		return (simplex_triangle(s, dir));
	}
	if (vec3_dot(vec3_cross(ad, ab), ao) > 0.0)
	{
		update_simplex3(s, 2, 0, 3);
		return (simplex_triangle(s, dir));
	}
	return (true);
}
