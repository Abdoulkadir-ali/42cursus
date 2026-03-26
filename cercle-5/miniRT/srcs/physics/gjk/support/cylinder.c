/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:07:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief GJK support point for a cylinder.
 */
t_vec3	gjk_support_cylinder(const void *data, t_vec3 dir)
{
	const t_cylinder	*cy;
	t_vec3				ax;
	t_vec3				lat;
	double				d[2];

	cy = (const t_cylinder *)data;
	ax = vec3_norm(cy->transform.forward);
	d[0] = vec3_dot(ax, dir);
	lat = vec3_sub(dir, vec3_scale(ax, d[0]));
	d[1] = vec3_mag(lat);
	if (d[1] > 1e-9)
		lat = vec3_scale(lat, cy->transform.scale.x / d[1]);
	else
		lat = vec3(0, 0, 0);
	if (d[0] >= 0.0)
		return (vec3_add(vec3_add(cy->phys.center,
					vec3_scale(ax, cy->transform.scale.y * 0.5)), lat));
	return (vec3_add(vec3_sub(cy->phys.center,
				vec3_scale(ax, cy->transform.scale.y * 0.5)), lat));
}
