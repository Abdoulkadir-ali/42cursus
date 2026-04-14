/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 12:17:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Initializes inertia for a capsule shape.
 */
static void	init_capsule_inertia(t_capsule *cap)
{
	double	r2;
	double	h2;

	if (cap->phys.mass < 1e-6)
		cap->phys.mass = 1.0;
	if (vec3_mag_sq(cap->phys.inv_inertia) > 1e-9)
		return ;
	r2 = cap->radius * cap->radius + 1e-9;
	h2 = 4.0 * cap->half_height * cap->half_height;
	cap->phys.inv_inertia.x = 12.0 / (3.0 * r2 + h2);
	cap->phys.inv_inertia.y = 2.0 / r2;
	cap->phys.inv_inertia.z = 12.0 / (3.0 * r2 + h2);
}

/**
 * @brief Updates transformation of the capsule.
 */
static void	update_state(t_capsule *cap, double dt, t_vec3 rot_d, t_vec3 delta)
{
	t_vec3	rot;

	cap->transform.rotation.pitch += rot_d.x;
	cap->transform.rotation.yaw += rot_d.y;
	cap->transform.rotation.roll += rot_d.z;
	rot = rot_by_ang(cap->axis, cap->phys.angular_velocity, dt);
	cap->axis = vec3_norm(rot);
	cap->transform.pos = vec3_add(cap->transform.pos, delta);
	cap->phys.center = cap->transform.pos;
}

static void	sanitize_capsule_vels(t_capsule *cap)
{
	if (!isfinite(cap->phys.velocity.x) || !isfinite(cap->phys.velocity.y)
		|| !isfinite(cap->phys.velocity.z))
		cap->phys.velocity = vec3(0, 0, 0);
	if (!isfinite(cap->phys.angular_velocity.x)
		|| !isfinite(cap->phys.angular_velocity.y)
		|| !isfinite(cap->phys.angular_velocity.z))
		cap->phys.angular_velocity = vec3(0, 0, 0);
}

static void	apply_capsule_vel(t_capsule *cap, double dt,
					t_physics_settings *s)
{
	t_vec2	damp;

	clamp_accel(&cap->phys);
	cap->phys.velocity = vec3_add(cap->phys.velocity,
			vec3_add(vec3_scale(s->gravity, dt),
				vec3_scale(cap->phys.accel, dt)));
	cap->phys.accel = vec3(0, 0, 0);
	damp.x = clamp_d(1.0 - s->global_damping * dt, 0, 1);
	damp.y = clamp_d(1.0 - s->global_damping * 0.5 * dt, 0, 1);
	cap->phys.velocity = vec3_scale(cap->phys.velocity, damp.x);
	clamp_speed(&cap->phys);
	cap->phys.angular_velocity = vec3_scale(cap->phys.angular_velocity, damp.y);
}

/**
 * @brief Integrates a capsule through one time step.
 */
void	integrate_capsule(t_capsule *cap, double dt, t_physics_settings *s)
{
	t_vec3	rot;

	if (cap->phys.is_static || cap->phys.is_sleeping)
		return ;
	check_sleep(&cap->phys, dt);
	if (cap->phys.is_sleeping)
		return ;
	init_capsule_inertia(cap);
	sanitize_capsule_vels(cap);
	apply_capsule_vel(cap, dt, s);
	rot = vec3_scale(cap->phys.angular_velocity, dt * (180.0 / M_PI));
	update_state(cap, dt, rot, vec3_scale(cap->phys.velocity, dt));
	cap->phys.pos = cap->transform.pos;
	phys_heat_viscous(&cap->phys, dt);
	phys_cool_radiative(&cap->phys, dt);
}
