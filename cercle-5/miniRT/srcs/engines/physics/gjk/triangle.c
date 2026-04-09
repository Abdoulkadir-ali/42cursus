/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 17:47:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

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
	{
		if (fabs(ab.x) < 0.9)
			*dir = vec3_cross(ab, vec3(1, 0, 0));
		else
			*dir = vec3_cross(ab, vec3(0, 1, 0));
	}
}

static bool	handle_triangle_edges(t_simplex *s, t_vec3 *dir, t_vec3 ab,
				t_vec3 ac)
{
	t_vec3	ao;
	t_vec3	abc;

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
		return (true);
	}
	return (false);
}

static bool	check_triangle_abc(t_simplex *s, t_vec3 *dir, t_vec3 ab, t_vec3 ao)
{
	t_vec3	abc;

	abc = vec3_cross(ab, vec3_sub(s->pts[0], s->pts[2]));
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
		return (true);
	}
	if (vec3_dot(abc, ao) < 0.0)
		reorder_simplex(s);
	if (vec3_dot(abc, ao) < 0.0)
		*dir = vec3_scale(abc, -1.0);
	else
		*dir = abc;
	return (false);
}

bool	gjk_simplex_triangle(t_simplex *s, t_vec3 *dir)
{
	t_vec3	ab;
	t_vec3	ac;
	t_vec3	ao;

	ab = vec3_sub(s->pts[1], s->pts[2]);
	ac = vec3_sub(s->pts[0], s->pts[2]);
	if (handle_triangle_edges(s, dir, ab, ac))
		return (false);
	ao = vec3_scale(s->pts[2], -1.0);
	return (check_triangle_abc(s, dir, ab, ao));
}
