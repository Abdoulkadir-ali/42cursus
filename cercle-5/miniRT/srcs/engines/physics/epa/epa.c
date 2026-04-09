/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 10:48:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Performs one expansion step of the EPA algorithm.
 */
static bool	epa_step(t_col_pair *p, t_epa_poly *poly, t_epa_res *res)
{
	t_epa_face	*f;
	t_vec3		v[3];
	t_edge		edges[EPA_MAX_VERTS * 3];
	size_t		n_e;

	f = &poly->faces[epa_closest_face(poly)];
	v[1] = p->sa->support(p->sa->data, f->normal);
	v[2] = p->sb->support(p->sb->data, vec3_scale(f->normal, -1.0));
	v[0] = vec3_sub(v[1], v[2]);
	if (vec3_dot(f->normal, v[0]) - f->dist < EPA_TOL)
	{
		epa_interpolate(poly, f, res);
		return (true);
	}
	epa_collect_silhouette(poly, v[0], edges, &n_e);
	epa_expand_poly(poly, v, edges, n_e);
	return (false);
}

/**
 * @brief Main Expanding Polytope Algorithm entry point.
 */
bool	gjk_epa(t_col_pair *p, t_simplex *s, t_epa_res *res)
{
	t_epa_poly	poly;
	size_t		iter;

	epa_init_poly(&poly, s);
	if (poly.n_faces == 0)
		return (false);
	iter = 0;
	while (iter < EPA_MAX_ITER)
	{
		if (epa_step(p, &poly, res))
			return (true);
		iter++;
	}
	epa_interpolate(&poly, &poly.faces[epa_closest_face(&poly)], res);
	if (vec3_mag_sq(res->normal) < 1e-12)
		return (false);
	return (true);
}
