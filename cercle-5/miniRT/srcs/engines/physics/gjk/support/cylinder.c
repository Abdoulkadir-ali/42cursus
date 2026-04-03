/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Returns the furthest point of a cylinder along the search direction.
 */
t_vec3	gjk_support_cylinder(const void *data, t_vec3 dir)
{
	const t_cylinder	*cy;
	t_vec3				ax;
	t_vec3				lat;
	double				axial_dot;
	double				lat_len;

	cy = (const t_cylinder *)data;
	ax = vec3_norm(cy->transform.forward);
	axial_dot = vec3_dot(ax, dir);
	lat = vec3_sub(dir, vec3_scale(ax, axial_dot));
	lat_len = vec3_mag(lat);
	if (lat_len > 1e-9)
		lat = vec3_scale(lat, cy->transform.scale.x / lat_len);
	else
		lat = vec3(0, 0, 0);
	if (axial_dot >= 0.0)
		return (vec3_add(vec3_add(cy->phys.center,
					vec3_scale(ax, cy->transform.scale.y * 0.5)), lat));
	return (vec3_add(vec3_sub(cy->phys.center,
				vec3_scale(ax, cy->transform.scale.y * 0.5)), lat));
}
