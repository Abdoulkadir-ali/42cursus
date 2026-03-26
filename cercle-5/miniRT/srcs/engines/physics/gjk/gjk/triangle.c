/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Updates a 4nd order simplex to a 3rd order.
 * Ensures original support points are correctly preserved for EPA.
 */
void	update_simplex3(t_simplex *s, int i0, int i1, int i2)
{
	t_vec3	p[3];
	t_vec3	pa[3];
	t_vec3	pb[3];

	p[0] = s->pts[i0];
	p[1] = s->pts[i1];
	p[2] = s->pts[i2];
	pa[0] = s->a_pts[i0];
	pa[1] = s->a_pts[i1];
	pa[2] = s->a_pts[i2];
	pb[0] = s->b_pts[i0];
	pb[1] = s->b_pts[i1];
	pb[2] = s->b_pts[i2];
	s->pts[0] = p[0];
	s->pts[1] = p[1];
	s->pts[2] = p[2];
	s->a_pts[0] = pa[0];
	s->a_pts[1] = pa[1];
	s->a_pts[2] = pa[2];
	s->b_pts[0] = pb[0];
	s->b_pts[1] = pb[1];
	s->b_pts[2] = pb[2];
	s->n = 3;
}

static bool	triangle_edge_cases(t_simplex *s, t_vec3 *dir, t_vec3 ab[2],
	t_vec3 ao_abc[2])
{
	if (vec3_dot(vec3_cross(ao_abc[1], ab[1]), ao_abc[0]) > 0.0)
	{
		if (vec3_dot(ab[1], ao_abc[0]) > 0.0)
		{
			s->pts[1] = s->pts[2];
			s->a_pts[1] = s->a_pts[2];
			s->b_pts[1] = s->b_pts[2];
			s->n = 2;
			*dir = vec3_triple_product(ab[1], ao_abc[0], ab[1]);
		}
		else
		{
			s->pts[0] = s->pts[1];
			s->pts[1] = s->pts[2];
			s->a_pts[0] = s->a_pts[1];
			s->a_pts[1] = s->a_pts[2];
			s->b_pts[0] = s->b_pts[1];
			s->b_pts[1] = s->b_pts[2];
			s->n = 2;
			*dir = vec3_triple_product(ab[0], ao_abc[0], ab[0]);
		}
		return (true);
	}
	return (false);
}

/**
 * @brief Handles GJK case for a 3rd order simplex (triangle).
 * Investigates regions around edges and the face normal.
 */
bool	simplex_triangle(t_simplex *s, t_vec3 *dir)
{
	t_vec3	ab[2];
	t_vec3	ao_abc[2];

	ab[0] = vec3_sub(s->pts[1], s->pts[2]);
	ab[1] = vec3_sub(s->pts[0], s->pts[2]);
	ao_abc[0] = vec3_scale(s->pts[2], -1.0);
	ao_abc[1] = vec3_cross(ab[0], ab[1]);
	if (triangle_edge_cases(s, dir, ab, ao_abc))
		return (false);
	if (vec3_dot(vec3_cross(ab[0], ao_abc[1]), ao_abc[0]) > 0.0)
	{
		s->pts[0] = s->pts[1];
		s->pts[1] = s->pts[2];
		s->a_pts[0] = s->a_pts[1];
		s->a_pts[1] = s->a_pts[2];
		s->b_pts[0] = s->b_pts[1];
		s->b_pts[1] = s->b_pts[2];
		s->n = 2;
		*dir = vec3_triple_product(ab[0], ao_abc[0], ab[0]);
		return (false);
	}
	if (vec3_dot(ao_abc[1], ao_abc[0]) < 0.0)
	{
		t_vec3 tmp;
		tmp = s->pts[0]; s->pts[0] = s->pts[1]; s->pts[1] = tmp;
		tmp = s->a_pts[0]; s->a_pts[0] = s->a_pts[1]; s->a_pts[1] = tmp;
		tmp = s->b_pts[0]; s->b_pts[0] = s->b_pts[1]; s->b_pts[1] = tmp;
		ao_abc[1] = vec3_scale(ao_abc[1], -1.0);
	}
	*dir = ao_abc[1];
	return (false);
}
