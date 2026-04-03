/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:13:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Initializes inertia for a cylinder shape.
 */
static void	init_cylinder_inertia(t_cylinder *cy)
{
	double	r2;
	double	h2;

	if (cy->phys.mass < 1e-6)
		cy->phys.mass = 1.0;
	if (vec3_mag_sq(cy->phys.inv_inertia) > 1e-9)
		return ;
	r2 = cy->transform.scale.x * cy->transform.scale.x + 1e-9;
	h2 = 4.0 * cy->transform.scale.y * cy->transform.scale.y;
	cy->phys.inv_inertia.x = 12.0 / (3.0 * r2 + h2);
	cy->phys.inv_inertia.y = 2.0 / r2;
	cy->phys.inv_inertia.z = 12.0 / (3.0 * r2 + h2);
}

/**
 * @brief Updates transformation of the cylinder.
 */
static void	update_state(t_cylinder *cy, double dt, t_vec3 rot_d, t_vec3 delta)
{
	cy->transform.rotation.pitch += rot_d.x;
	cy->transform.rotation.yaw += rot_d.y;
	cy->transform.rotation.roll += rot_d.z;
	cy->transform.forward = vec3_norm(rot_by_ang(cy->transform.forward,
				cy->phys.angular_velocity, dt));
	cy->transform.pos = vec3_add(cy->transform.pos, delta);
	cy->phys.center = vec3_add(cy->transform.pos,
			vec3_scale(vec3_norm(cy->transform.forward),
				cy->transform.scale.y * 0.5));
}

/**
 * @brief Integrates a cylinder body through one time step.
 */
void	integrate_cylinder(t_cylinder *cy, double dt, t_physics_settings *s)
{
	t_vec2	damp;
	t_vec3	rot;
	t_vec3	vel;

	if (cy->phys.is_static)
		return ;
	init_cylinder_inertia(cy);
	cy->phys.velocity = vec3_add(cy->phys.velocity, vec3_scale(s->gravity, dt));
	damp.x = clamp_d(1.0 - s->global_damping * dt, 0, 1);
	damp.y = clamp_d(1.0 - s->global_damping * 0.5 * dt, 0, 1);
	cy->phys.velocity = vec3_scale(cy->phys.velocity, damp.x);
	cy->phys.angular_velocity = vec3_scale(cy->phys.angular_velocity, damp.y);
	rot = vec3_scale(cy->phys.angular_velocity, dt * (180.0 / M_PI));
	vel = vec3_scale(cy->phys.velocity, dt);
	update_state(cy, dt, rot, vel);
}
