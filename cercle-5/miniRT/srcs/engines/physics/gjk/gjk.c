/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gjk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:20:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Dispatcher for GJK simplex sub-cases (line, triangle, tetrahedron).
 */
static bool	next_simplex(t_simplex *s, t_vec3 *dir)
{
	if (s->n == 2)
		return (gjk_simplex_line(s, dir));
	if (s->n == 3)
		return (gjk_simplex_triangle(s, dir));
	return (gjk_simplex_tetrahedron(s, dir));
}

/**
 * @brief Top-level GJK intersection test.
 * Fills 'out' simplex for the EPA algorithm on confirmed collision.
 */
bool	gjk_intersect(t_gjk_shape *a, t_gjk_shape *b, t_simplex *out)
{
	t_simplex	s;
	t_vec3		dir;
	size_t		iter;

	s.n = 0;
	dir = vec3_sub(b->center, a->center);
	if (vec3_mag_sq(dir) < 1e-9)
		dir = vec3(1, 0, 0);
	md_support(a, b, dir, &s);
	s.n = 1;
	dir = vec3_scale(s.pts[0], -1.0);
	iter = 0;
	while (iter < GJK_MAX_ITER)
	{
		if (vec3_mag_sq(dir) < 1e-12)
			break ;
		if (vec3_dot(md_support(a, b, dir, &s), dir) < 0.0)
			return (false);
		s.n++;
		if (next_simplex(&s, &dir))
			return (*out = s, true);
		iter++;
	}
	return (false);
}
