/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gjk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* *****************:********************************************************* */

#include "physics.h"

#define GJK_MAX_ITER 20

static bool	next_simplex(t_simplex *s, t_vec3 *dir)
{
	if (s->n == 2)
		return (simplex_line(s, dir));
	if (s->n == 3)
		return (simplex_triangle(s, dir));
	return (simplex_tetrahedron(s, dir));
}

/**
 * @brief GJK — Gilbert-Johnson-Keerthi collision detection.
 * Iteratively builds a simplex to enclose the origin in Minkowski space.
 */
bool	gjk_intersect(t_gjk_shape *a, t_gjk_shape *b, t_simplex *out)
{
	t_simplex	s;
	t_vec3		dir;
	t_vec3		pt[3];
	int			it;

	dir = vec3_sub(b->center, a->center);
	if (vec3_mag_sq(dir) < 1e-9)
		dir = vec3(1, 0, 0);
	pt[0] = md_support(a, b, dir, &pt[1], &pt[2]);
	s.pts[0] = pt[0]; s.a_pts[0] = pt[1]; s.b_pts[0] = pt[2];
	s.n = 1;
	dir = vec3_scale(pt[0], -1.0);
	it = -1;
	while (++it < GJK_MAX_ITER)
	{
		if (vec3_mag_sq(dir) < 1e-12)
			break ;
		pt[0] = md_support(a, b, dir, &pt[1], &pt[2]);
		if (vec3_dot(pt[0], dir) < 0.0)
			return (false);
		s.pts[s.n] = pt[0]; s.a_pts[s.n] = pt[1]; s.b_pts[s.n] = pt[2];
		s.n++;
		if (next_simplex(&s, &dir))
			return (*out = s, true);
	}
	return (false);
}
