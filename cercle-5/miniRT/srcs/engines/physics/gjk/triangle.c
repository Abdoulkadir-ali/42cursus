/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:19:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Handles edge logic for the triangle-simplex case.
 */
static void	triangle_edge(t_simplex *s, t_vec3 a, t_vec3 b, t_vec3 *dir)
{
	t_vec3	ab;
	t_vec3	ao;

	ab = vec3_sub(b, a);
	ao = vec3_scale(a, -1.0);
	s->pts[0] = b;
	s->pts[1] = a;
	s->a_pts[0] = s->a_pts[1];
	s->a_pts[1] = s->a_pts[2];
	s->b_pts[0] = s->b_pts[1];
	s->b_pts[1] = s->b_pts[2];
	s->n = 2;
	*dir = vec3_sub(vec3_scale(ao, vec3_dot(ab, ab)),
			vec3_scale(ab, vec3_dot(ao, ab)));
}

/**
 * @brief Reorders triangle simplex points to maintain CCW orientation.
 */
static void	reorder_simplex(t_simplex *s)
{
	t_vec3	tmp;

	tmp = s->pts[0];
	s->pts[0] = s->pts[1];
	s->pts[1] = tmp;
	tmp = s->a_pts[0];
	s->a_pts[0] = s->a_pts[1];
	s->a_pts[1] = tmp;
	tmp = s->b_pts[0];
	s->b_pts[0] = s->b_pts[1];
	s->b_pts[1] = tmp;
}

/**
 * @brief Handles the face-normal choice and CCW reordering for triangles.
 */
static void	triangle_face(t_simplex *s, t_vec3 abc, t_vec3 ao, t_vec3 *dir)
{
	if (vec3_dot(abc, ao) > 0.0)
		*dir = abc;
	else
	{
		reorder_simplex(s);
		*dir = vec3_scale(abc, -1.0);
	}
}

/**
 * @brief Main triangle-simplex case handler.
 */
bool	gjk_simplex_triangle(t_simplex *s, t_vec3 *dir)
{
	t_vec3	p[3];
	t_vec3	ab;
	t_vec3	ac;
	t_vec3	ao;

	p[2] = s->pts[2];
	p[1] = s->pts[1];
	p[0] = s->pts[0];
	ab = vec3_sub(p[1], p[2]);
	ac = vec3_sub(p[0], p[2]);
	ao = vec3_scale(p[2], -1.0);
	if (vec3_dot(vec3_cross(vec3_cross(ab, ac), ac), ao) > 0.0)
	{
		if (vec3_dot(ac, ao) > 0.0)
			triangle_edge(s, p[2], p[0], dir);
		else
			triangle_edge(s, p[2], p[1], dir);
		return (false);
	}
	if (vec3_dot(vec3_cross(ab, vec3_cross(ab, ac)), ao) > 0.0)
		return (triangle_edge(s, p[2], p[1], dir), false);
	triangle_face(s, vec3_cross(ab, ac), ao, dir);
	return (false);
}
