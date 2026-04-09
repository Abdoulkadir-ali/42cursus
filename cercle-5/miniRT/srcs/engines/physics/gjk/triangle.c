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
 * Ensures s->pts[0] and s->pts[1] correspond correctly to a_pts and b_pts.
 */
static void	set_simplex_edge(t_simplex *s, int i1, int i2, t_vec3 *dir)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	ab;
	t_vec3	ao;

	a = s->pts[i1];
	b = s->pts[i2];
	ab = vec3_sub(b, a);
	ao = vec3_scale(a, -1.0);
	s->pts[0] = b;
	s->pts[1] = a;
	s->a_pts[0] = s->a_pts[i2];
	s->a_pts[1] = s->a_pts[i1];
	s->b_pts[0] = s->b_pts[i2];
	s->b_pts[1] = s->b_pts[i1];
	s->n = 2;
	*dir = vec3_sub(vec3_scale(ao, vec3_dot(ab, ab)),
			vec3_scale(ab, vec3_dot(ao, ab)));
	if (vec3_mag_sq(*dir) < 1e-12)
		*dir = vec3_cross(ab, (fabs(ab.x) < 0.9) ? vec3(1, 0, 0) : vec3(0, 1, 0));
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
 * @brief Main triangle-simplex case handler.
 */
bool	gjk_simplex_triangle(t_simplex *s, t_vec3 *dir)
{
	t_vec3	ab;
	t_vec3	ac;
	t_vec3	ao;
	t_vec3	abc;

	ab = vec3_sub(s->pts[1], s->pts[2]);
	ac = vec3_sub(s->pts[0], s->pts[2]);
	ao = vec3_scale(s->pts[2], -1.0);
	abc = vec3_cross(ab, ac);
	if (vec3_dot(vec3_cross(abc, ac), ao) > 0.0)
	{
		if (vec3_dot(ac, ao) > 0.0)
			set_simplex_edge(s, 2, 0, dir);
		else if (vec3_dot(ab, ao) > 0.0)
			set_simplex_edge(s, 2, 1, dir);
		else
		{
			s->pts[0] = s->pts[2];
			s->a_pts[0] = s->a_pts[2];
			s->b_pts[0] = s->b_pts[2];
			s->n = 1;
			*dir = ao;
		}
		return (false);
	}
	if (vec3_dot(vec3_cross(ab, abc), ao) > 0.0)
	{
		if (vec3_dot(ab, ao) > 0.0)
			set_simplex_edge(s, 2, 1, dir);
		else
		{
			s->pts[0] = s->pts[2];
			s->a_pts[0] = s->a_pts[2];
			s->b_pts[0] = s->b_pts[2];
			s->n = 1;
			*dir = ao;
		}
		return (false);
	}
	if (vec3_dot(abc, ao) > 0.0)
		*dir = abc;
	else
	{
		reorder_simplex(s);
		*dir = vec3_scale(abc, -1.0);
	}
	return (false);
}
