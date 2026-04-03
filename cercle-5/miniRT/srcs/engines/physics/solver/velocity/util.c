/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:37:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Computes velocity of a point on a rigid body.
 * v_point = linear_velocity + angular_velocity x r
 */
t_vec3	point_vel(t_physics_body *body, t_vec3 r)
{
	if (!body)
		return (vec3(0, 0, 0));
	return (vec3_add(body->velocity, vec3_cross(body->angular_velocity, r)));
}

/**
 * @brief Computes angular term for impulse calculation.
 */
double	ang_term(t_physics_body *body, t_vec3 r, t_vec3 dir, double inv_m)
{
	t_vec3	rn;
	t_vec3	torque;

	if (!body || body->is_static || inv_m <= 0.0)
		return (0.0);
	rn = vec3_cross(r, dir);
	torque = vec3_mul(body->inv_inertia, rn);
	return (vec3_dot(vec3_cross(torque, r), dir));
}
