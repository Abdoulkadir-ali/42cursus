/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Minkowski-difference support: S = support_A(dir) - support_B(-dir).
 * Updates the simplex with the new points at index s->n.
 */
t_vec3	md_support(t_gjk_shape *a, t_gjk_shape *b, t_vec3 dir, t_simplex *s)
{
	s->a_pts[s->n] = a->support(a->data, dir);
	s->b_pts[s->n] = b->support(b->data, vec3_scale(dir, -1.0));
	s->pts[s->n] = vec3_sub(s->a_pts[s->n], s->b_pts[s->n]);
	return (s->pts[s->n]);
}

/**
 * @brief Updates the simplex to a specific triangle (3 points) in-place.
 */
void	set_simplex3(t_simplex *s, size_t *i, t_vec3 *p)
{
	t_vec3	sa[3];
	t_vec3	sb[3];

	sa[0] = s->a_pts[i[2]];
	sa[1] = s->a_pts[i[1]];
	sa[2] = s->a_pts[i[0]];
	sb[0] = s->b_pts[i[2]];
	sb[1] = s->b_pts[i[1]];
	sb[2] = s->b_pts[i[0]];
	s->pts[0] = p[2];
	s->pts[1] = p[1];
	s->pts[2] = p[0];
	s->a_pts[0] = sa[0];
	s->a_pts[1] = sa[1];
	s->a_pts[2] = sa[2];
	s->b_pts[0] = sb[0];
	s->b_pts[1] = sb[1];
	s->b_pts[2] = sb[2];
	s->n = 3;
}

void	reorder_simplex(t_simplex *s)
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
