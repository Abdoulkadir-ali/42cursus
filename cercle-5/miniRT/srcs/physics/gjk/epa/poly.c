/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Initializes the initial EPA polytope from a GJK tetrahedron or triangle.
 */
void	init_polytope(t_epa_poly *p, t_simplex *s)
{
	int	i;

	i = -1;
	while (++i < s->n && i < EPA_MAX_VERTS)
	{
		p->pts[i] = s->pts[i];
		p->a_pts[i] = s->a_pts[i];
		p->b_pts[i] = s->b_pts[i];
	}
	p->n_verts = s->n;
	p->n_faces = 0;
	if (s->n == 4)
	{
		p->faces[0] = make_face(p, 0, 1, 2);
		p->faces[1] = make_face(p, 0, 1, 3);
		p->faces[2] = make_face(p, 0, 2, 3);
		p->faces[3] = make_face(p, 1, 2, 3);
		p->n_faces = 4;
	}
	else if (s->n == 3)
	{
		p->faces[0] = make_face(p, 0, 1, 2);
		p->faces[1] = make_face(p, 0, 2, 1);
		p->n_faces = 2;
	}
}

/**
 * @brief Returns the index of the face closest to the origin.
 */
int	closest_face(t_epa_poly *p)
{
	int		best;
	double	best_d;
	int		i;

	best = 0;
	best_d = p->faces[0].dist;
	i = 0;
	while (++i < p->n_faces)
	{
		if (p->faces[i].dist < best_d)
		{
			best_d = p->faces[i].dist;
			best = i;
		}
	}
	return (best);
}
