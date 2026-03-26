/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Interpolates support points using barycentric coordinates to derive
 * the final world-space contact points for both shapes.
 */
void	get_contact_points(t_epa_poly *poly, t_epa_face *f,
		t_vec3 *ca, t_vec3 *cb)
{
	t_vec3	w;
	t_vec3	tri[3];

	tri[0] = poly->pts[f->idx[0]];
	tri[1] = poly->pts[f->idx[1]];
	tri[2] = poly->pts[f->idx[2]];
	w = bary(tri, vec3_scale(f->normal, f->dist));
	*ca = vec3_add(vec3_add(vec3_scale(poly->a_pts[f->idx[0]], w.x),
				vec3_scale(poly->a_pts[f->idx[1]], w.y)),
			vec3_scale(poly->a_pts[f->idx[2]], w.z));
	*cb = vec3_add(vec3_add(vec3_scale(poly->b_pts[f->idx[0]], w.x),
				vec3_scale(poly->b_pts[f->idx[1]], w.y)),
			vec3_scale(poly->b_pts[f->idx[2]], w.z));
}
