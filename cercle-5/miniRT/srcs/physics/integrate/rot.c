/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 03:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 03:36:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include <math.h>

/**
 * @brief Rodrigues rotation: rotate vector v by angular_velocity vector w over
 * time interval dt.
 */
t_vec3	rot_by_ang(t_vec3 v, t_vec3 w, double dt)
{
	double	theta;
	t_vec3	n;
	double	c;
	double	s;

	theta = vec3_mag(w) * dt;
	if (theta < 1e-9)
		return (v);
	n = vec3_norm(w);
	c = cos(theta);
	s = sin(theta);
	return (vec3_add(vec3_add(vec3_scale(v, c),
				vec3_scale(vec3_cross(n, v), s)),
			vec3_scale(n, vec3_dot(n, v) * (1.0 - c))));
}
