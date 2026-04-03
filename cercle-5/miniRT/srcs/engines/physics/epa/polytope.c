/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polytope.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:07:03 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:07:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Helper for face initialization.
 */
static void	epa_init_faces(t_epa_poly *p, t_simplex *s)
{
	if (s->n == 4)
	{
		p->faces[0] = epa_make_face(p, 0, 1, 2);
		p->faces[1] = epa_make_face(p, 0, 1, 3);
		p->faces[2] = epa_make_face(p, 0, 2, 3);
		p->faces[3] = epa_make_face(p, 1, 2, 3);
		p->n_faces = 4;
	}
	else if (s->n == 3)
	{
		p->faces[0] = epa_make_face(p, 0, 1, 2);
		p->faces[1] = epa_make_face(p, 0, 2, 1);
		p->n_faces = 2;
	}
}

/**
 * @brief Builds the initial polytope from the GJK simplex.
 */
void	epa_init_poly(t_epa_poly *p, t_simplex *s)
{
	size_t	i;

	i = 0;
	while (i < s->n && i < EPA_MAX_VERTS)
	{
		p->pts[i] = s->pts[i];
		p->a_pts[i] = s->a_pts[i];
		p->b_pts[i] = s->b_pts[i];
		i++;
	}
	p->n_verts = s->n;
	p->n_faces = 0;
	epa_init_faces(p, s);
}

/**
 * @brief Expands the polytope by adding a new vertex and connecting faces.
 */
void	epa_expand_poly(t_epa_poly *p, t_vec3 *v, t_edge *e, size_t n_e)
{
	size_t	vi;
	size_t	i;

	if (p->n_verts >= EPA_MAX_VERTS)
		return ;
	vi = p->n_verts++;
	p->pts[vi] = v[0];
	p->a_pts[vi] = v[1];
	p->b_pts[vi] = v[2];
	i = 0;
	while (i < n_e && p->n_faces < EPA_MAX_FACES)
	{
		p->faces[p->n_faces] = epa_make_face(p, e[i].a, e[i].b, vi);
		p->n_faces++;
		i++;
	}
}
