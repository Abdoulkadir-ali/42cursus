/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	epa_loop(t_gjk_shape *a, t_gjk_shape *b, t_epa_poly *poly,
		t_epa_res *res)
{
	t_edge	edges[EPA_MAX_VERTS * 3];
	t_vec3	pt[3];
	int		v[3];

	v[0] = -1;
	while (++v[0] < EPA_MAX_ITER)
	{
		res->f = &poly->faces[closest_face(poly)];
		pt[1] = a->support(a, ((t_epa_face *)res->f)->normal);
		pt[2] = b->support(b, vec3_scale(((t_epa_face *)res->f)->normal, -1.0));
		pt[0] = vec3_sub(pt[1], pt[2]);
		if (vec3_dot(((t_epa_face *)res->f)->normal, pt[0])
			- ((t_epa_face *)res->f)->dist < EPA_TOL)
			break ;
		collect_silhouette(poly, pt[0], edges, &v[1]);
		if (poly->n_verts >= EPA_MAX_VERTS)
			break ;
		v[2] = poly->n_verts++;
		poly->pts[v[2]] = pt[0]; poly->a_pts[v[2]] = pt[1]; poly->b_pts[v[2]] = pt[2];
		while (v[1]-- > 0 && poly->n_faces < EPA_MAX_FACES)
			poly->faces[poly->n_faces++] = make_face(poly, edges[v[1]].a,
				edges[v[1]].b, v[2]);
	}
}

/**
 * @brief EPA — Expanding Polytope Algorithm.
 * Iteratively expands the Minkowski boundary to find the MTD.
 */
bool	gjk_epa(t_gjk_shape *a, t_gjk_shape *b, t_simplex *s, t_epa_res *res)
{
	t_epa_poly	poly;

	init_polytope(&poly, s);
	if (poly.n_faces == 0)
		return (false);
	epa_loop(a, b, &poly, res);
	get_contact_points(&poly, (t_epa_face *)res->f, &res->contact_a,
		&res->contact_b);
	res->normal = ((t_epa_face *)res->f)->normal;
	res->depth = ((t_epa_face *)res->f)->dist;
	return (true);
}
