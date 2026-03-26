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

/**
 * @brief Safely returns 1.0/mass or 0.0 for static/infinite mass bodies.
 */
double	get_inv_mass(t_physics_body *body)
{
	if (!body || body->mass <= 1e-6 || body->is_static)
		return (0.0);
	return (1.0 / body->mass);
}

/**
 * @brief Computes the point velocity of a body at distance r from COM.
 */
t_vec3	point_vel(t_physics_body *body, t_vec3 r)
{
	if (!body)
		return (vec3(0, 0, 0));
	return (vec3_add(body->velocity,
			vec3_cross(body->angular_velocity, r)));
}

/**
 * @brief Projected angular inertia term along a given axis (dir).
 */
double	ang_term(t_physics_body *body, t_vec3 r, t_vec3 dir, double inv_m)
{
	t_vec3	rxd;

	if (!body || inv_m < 1e-9)
		return (0.0);
	rxd = vec3_cross(r, dir);
	return (inv_m * (rxd.x * rxd.x * body->inv_inertia.x
			+ rxd.y * rxd.y * body->inv_inertia.y
			+ rxd.z * rxd.z * body->inv_inertia.z));
}

/**
 * @brief Utility for applying impulsive torque to a body.
 */
void	apply_solver_torque(t_physics_body *body, t_vec3 r, t_vec3 imp,
		double inv_m, double sign)
{
	t_vec3	torque;
	t_vec3	dw;

	torque = vec3_cross(r, vec3_scale(imp, sign));
	dw.x = torque.x * inv_m * body->inv_inertia.x;
	dw.y = torque.y * inv_m * body->inv_inertia.y;
	dw.z = torque.z * inv_m * body->inv_inertia.z;
	body->angular_velocity = vec3_add(body->angular_velocity, dw);
}
