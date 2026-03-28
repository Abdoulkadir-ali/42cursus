/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:19:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief DOD-compliant GJK support point for a cylinder.
 * Fetches axis, radius, and height directly from the primitive SoA.
 */
t_vec3	gjk_support_cylinder(const t_gjk_shape *s, t_vec3 dir)
{
	t_cylinder	cy;
	t_vec3		lat;
	double		dot_axis;
	double		lat_mag;

	cy = unpack_cylinder(&s->scene->primitives, s->idx);
	dot_axis = vec3_dot(cy.axis, dir);
	lat = vec3_sub(dir, vec3_scale(cy.axis, dot_axis));
	lat_mag = vec3_mag(lat);
	if (lat_mag > 1e-9)
		lat = vec3_scale(lat, cy.radius / lat_mag);
	else
		lat = vec3(0, 0, 0);
	if (dot_axis >= 0.0)
		return (vec3_add(vec3_add(cy.pos, vec3_scale(cy.axis, cy.height)), lat));
	return (vec3_add(cy.pos, lat));
}
