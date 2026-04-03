/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:13:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Initializes inertia for a pyramid shape.
 */
static void	init_pyramid_inertia(t_pyramid *py)
{
	double	s2;
	double	h2;

	if (py->phys.mass < 1e-6)
		py->phys.mass = 1.0;
	if (vec3_mag_sq(py->phys.inv_inertia) > 1e-9)
		return ;
	s2 = py->base_size * py->base_size + 1e-9;
	h2 = py->height * py->height + 1e-9;
	py->phys.inv_inertia = vec3(10.0 / (s2 * 0.25 + h2 * 0.4), 6.0 / s2,
			10.0 / (s2 * 0.25 + h2 * 0.4));
}

/**
 * @brief Updates transformation of the pyramid.
 */
static void	update_state(t_pyramid *py, double dt, t_vec3 rot_d, t_vec3 delta)
{
	py->transform.rotation.pitch += rot_d.x;
	py->transform.rotation.yaw += rot_d.y;
	py->transform.rotation.roll += rot_d.z;
	py->up = vec3_norm(rot_by_ang(py->up, py->phys.angular_velocity, dt));
	py->transform.pos = vec3_add(py->transform.pos, delta);
	py->phys.center = vec3_add(py->transform.pos,
			vec3_scale(py->up, py->height * 0.25));
}

/**
 * @brief Integrates a pyramid shape through one time step.
 */
void	integrate_pyramid(t_pyramid *py, double dt, t_physics_settings *s)
{
	t_vec2	damp;
	t_vec3	rot;

	if (py->phys.is_static)
		return ;
	init_pyramid_inertia(py);
	py->phys.velocity = vec3_add(py->phys.velocity, vec3_scale(s->gravity, dt));
	damp.x = clamp_d(1.0 - s->global_damping * dt, 0, 1);
	damp.y = clamp_d(1.0 - s->global_damping * 0.5 * dt, 0, 1);
	py->phys.velocity = vec3_scale(py->phys.velocity, damp.x);
	py->phys.angular_velocity = vec3_scale(py->phys.angular_velocity, damp.y);
	rot = vec3_scale(py->phys.angular_velocity, dt * (180.0 / M_PI));
	update_state(py, dt, rot, vec3_scale(py->phys.velocity, dt));
}
