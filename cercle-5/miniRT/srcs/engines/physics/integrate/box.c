/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 20:48:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Initializes inertia for a box primitive.
 */
static void	init_box_inertia(t_box *bx)
{
	t_vec3	e;

	if (bx->phys.mass < 1e-6)
		bx->phys.mass = 1.0;
	if (vec3_mag_sq(bx->phys.inv_inertia) > 1e-9)
		return ;
	e = bx->half_extents;
	bx->phys.inv_inertia.x = 3.0 / (e.y * e.y + e.z * e.z + 1e-9);
	bx->phys.inv_inertia.y = 3.0 / (e.x * e.x + e.z * e.z + 1e-9);
	bx->phys.inv_inertia.z = 3.0 / (e.x * e.x + e.y * e.y + 1e-9);
}

/**
 * @brief Updates rotation and center position for a box.
 */
static void	update_state(t_box *bx, double dt, t_vec3 delta)
{
	t_vec3	rot_d;

	rot_d = vec3_scale(bx->phys.angular_velocity, dt * (180.0 / M_PI));
	bx->transform.rotation.pitch += rot_d.x;
	bx->transform.rotation.yaw += rot_d.y;
	bx->transform.rotation.roll += rot_d.z;
	bx->transform.forward = vec3_norm(rot_by_ang(bx->transform.forward,
				bx->phys.angular_velocity, dt));
	bx->transform.right = vec3_norm(rot_by_ang(bx->transform.right,
				bx->phys.angular_velocity, dt));
	bx->transform.up = vec3_norm(rot_by_ang(bx->transform.up,
				bx->phys.angular_velocity, dt));
	bx->transform.pos = vec3_add(bx->transform.pos, delta);
	bx->phys.center = bx->transform.pos;
}

/**
 * @brief Integrates a oriented bounding box body through one time step.
 */
void	integrate_box(t_box *bx, double dt, t_physics_settings *s)
{
	t_vec3	v_d;
	t_vec2	damp;

	if (bx->phys.is_static)
		return ;
	init_box_inertia(bx);
	bx->phys.velocity = vec3_add(bx->phys.velocity,
			vec3_add(vec3_scale(s->gravity, dt),
				vec3_scale(bx->phys.accel, dt)));
	bx->phys.accel = vec3(0, 0, 0);
	damp.x = clamp_d(1.0 - s->global_damping * dt, 0, 1);
	damp.y = clamp_d(1.0 - s->global_damping * 0.5 * dt, 0, 1);
	bx->phys.velocity = vec3_scale(bx->phys.velocity, damp.x);
	bx->phys.angular_velocity = vec3_scale(bx->phys.angular_velocity, damp.y);
	v_d = vec3_scale(bx->phys.velocity, dt);
	update_state(bx, dt, v_d);
	bx->phys.pos = bx->transform.pos;
}
