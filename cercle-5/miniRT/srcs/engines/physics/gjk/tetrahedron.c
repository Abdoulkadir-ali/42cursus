/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrahedron.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Checks if origin is in front of a tetrahedron face.
 */
static bool	check_face(t_simplex *s, size_t *idx, t_vec3 *p, t_vec3 *dir)
{
	t_vec3	abc;

	abc = vec3_cross(vec3_sub(p[idx[1]], p[idx[0]]),
			vec3_sub(p[idx[2]], p[idx[0]]));
	if (vec3_dot(abc, vec3_scale(p[idx[0]], -1.0)) > 0.0)
	{
		set_simplex3(s, idx, p);
		return (gjk_simplex_triangle(s, dir));
	}
	return (false);
}

/**
 * @brief Handles the tetrahedron-simplex case.
 */
bool	gjk_simplex_tetrahedron(t_simplex *s, t_vec3 *dir)
{
	t_vec3	p[4];
	size_t	i[3];

	p[3] = s->pts[3];
	p[2] = s->pts[2];
	p[1] = s->pts[1];
	p[0] = s->pts[0];
	i[0] = 3;
	i[1] = 2;
	i[2] = 1;
	if (check_face(s, i, p, dir))
		return (false);
	i[1] = 1;
	i[2] = 0;
	if (check_face(s, i, p, dir))
		return (false);
	i[1] = 0;
	i[2] = 2;
	if (check_face(s, i, p, dir))
		return (false);
	return (true);
}
