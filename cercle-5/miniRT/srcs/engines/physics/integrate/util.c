/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:13:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Performs Rodrigues rotation of vector v by angular velocity w * dt.
 */
t_vec3	rot_by_ang(t_vec3 v, t_vec3 w, double dt)
{
	double	th;
	t_vec3	n;

	th = vec3_mag(w) * dt;
	if (th < 1e-9)
		return (v);
	n = vec3_norm(w);
	return (vec3_add(vec3_add(vec3_scale(v, cos(th)),
				vec3_scale(vec3_cross(n, v), sin(th))),
			vec3_scale(n, vec3_dot(n, v) * (1.0 - cos(th)))));
}
