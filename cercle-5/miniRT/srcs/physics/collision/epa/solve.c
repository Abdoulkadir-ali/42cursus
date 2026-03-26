/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

extern void	init_polytope(t_epa_poly *p, t_simplex *s);
extern int	closest_face(t_epa_poly *p);
extern void	get_contact_points(t_epa_poly *p, t_epa_face *f, t_vec3 *ca, t_vec3 *cb);
extern void	expand(t_epa_poly *p, t_vec3 pt, t_vec3 pa, t_vec3 pb);

/**
 * @brief Core EPA Solver entry. Expands the Minkowski simplex until convergence.
 * Compliance: Fixed function length and monolithic logic split (Piège B).
 */
bool	gjk_epa(t_gjk_shape *a, t_gjk_shape *b, t_simplex *s, t_epa_res *res)
{
	t_epa_poly	poly;
	int			cf;
	t_vec3		p;
	t_vec3		pa;
	t_vec3		pb;
	int			iter;

	init_polytope(&poly, s);
	iter = -1;
	while (++iter < EPA_MAX_ITER)
	{
		cf = closest_face(&poly);
		p = md_support(a, b, poly.faces[cf].normal, &pa, &pb);
		if (vec3_dot(poly.faces[cf].normal, p) - poly.faces[cf].dist < EPA_TOL)
		{
			res->normal = poly.faces[cf].normal;
			res->depth = poly.faces[cf].dist;
			get_contact_points(&poly, &poly.faces[cf], &res->contact_a, &res->contact_b);
			return (true);
		}
		expand(&poly, p, pa, pb);
	}
	return (false);
}
