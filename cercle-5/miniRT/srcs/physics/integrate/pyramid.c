/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:07:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

static void	init_pyramid_inertia(t_pyramid *py)
{
	t_vec3	inv_i;
	double	s2;
	double	h2;

	s2 = py->base_size * py->base_size + 1e-9;
	h2 = py->height * py->height + 1e-9;
	inv_i.x = 10.0 / (s2 * 0.25 + h2 * 0.4);
	inv_i.y = 6.0 / s2;
	inv_i.z = 10.0 / (s2 * 0.25 + h2 * 0.4);
	py->phys.inv_inertia = mat3_diag(inv_i);
}

/**
 * @brief Logic to update the pyramid's physical state.
 * Uses global physics constants.
 */
void	integrate_pyramid(t_pyramid *py, double dt)
{
	t_vec3	rot;

	if (py->phys.is_static)
		return ;
	if (py->phys.mass < 1e-6)
		py->phys.mass = 1.0;
	if (py->phys.inv_inertia.m[0][0] < 1e-9)
		init_pyramid_inertia(py);
	py->phys.velocity = vec3_add(py->phys.velocity,
			vec3_scale(gravity_vec(), dt));
	py->phys.velocity = vec3_scale(py->phys.velocity,
			clamp_d(1.0 - GLOBAL_DAMPING * dt, 0, 1));
	py->phys.angular_velocity = vec3_scale(py->phys.angular_velocity,
			clamp_d(1.0 - GLOBAL_DAMPING * 0.5 * dt, 0, 1));
	rot = vec3_scale(py->phys.angular_velocity, dt * (180.0 / M_PI));
	py->transform.rotation.pitch += rot.x;
	py->transform.rotation.yaw += rot.y;
	py->transform.rotation.roll += rot.z;
	py->up = vec3_norm(rot_by_ang(py->up, py->phys.angular_velocity, dt));
	py->transform.pos = vec3_add(py->transform.pos,
			vec3_scale(py->phys.velocity, dt));
	py->phys.center = vec3_add(py->transform.pos,
			vec3_scale(py->up, py->height * 0.25));
}
