/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 12:17:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Recomputes and caches the 5 world-space pyramid vertices into
 *        py->c[0..3] (base corners) and py->apex after every integration step.
 *        Mirrors pyramid_cache_verts() from the raytracing module so that
 *        the physics support function and plane-contact code can read them
 *        directly without recomputing on every GJK/EPA query.
 */
static void	pyramid_update_verts(t_pyramid *py)
{
	t_vec3	ref;
	t_vec3	right;
	t_vec3	fwd;
	double	h;

	h = py->base_size * 0.5;
	if (fabs(py->up.y) < 0.9)
		ref = vec3(0, 1, 0);
	else
		ref = vec3(1, 0, 0);
	right = vec3_norm(vec3_cross(py->up, ref));
	fwd = vec3_cross(right, py->up);
	py->c[0] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, h)),
			vec3_scale(fwd, h));
	py->c[1] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, -h)),
			vec3_scale(fwd, h));
	py->c[2] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, -h)),
			vec3_scale(fwd, -h));
	py->c[3] = vec3_add(vec3_add(py->transform.pos, vec3_scale(right, h)),
			vec3_scale(fwd, -h));
	py->apex = vec3_add(py->transform.pos, vec3_scale(py->up, py->height));
}

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
	t_vec3	center;

	py->transform.rotation.pitch += rot_d.x;
	py->transform.rotation.yaw += rot_d.y;
	py->transform.rotation.roll += rot_d.z;
	py->up = vec3_norm(rot_by_ang(py->up, py->phys.angular_velocity, dt));
	center = vec3_add(py->phys.center, delta);
	py->transform.pos = vec3_sub(center,
			vec3_scale(py->up, py->height * 0.25));
	py->phys.center = center;
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
	clamp_accel(&py->phys);
	py->phys.velocity = vec3_add(py->phys.velocity,
			vec3_add(vec3_scale(s->gravity, dt),
				vec3_scale(py->phys.accel, dt)));
	py->phys.accel = vec3(0, 0, 0);
	damp.x = clamp_d(1.0 - s->global_damping * dt, 0, 1);
	damp.y = clamp_d(1.0 - s->global_damping * 0.5 * dt, 0, 1);
	py->phys.velocity = vec3_scale(py->phys.velocity, damp.x);
	clamp_speed(&py->phys);
	py->phys.angular_velocity = vec3_scale(py->phys.angular_velocity, damp.y);
	rot = vec3_scale(py->phys.angular_velocity, dt * (180.0 / M_PI));
	update_state(py, dt, rot, vec3_scale(py->phys.velocity, dt));
	py->phys.pos = py->transform.pos;
	pyramid_update_verts(py);
	phys_heat_viscous(&py->phys, dt);
	phys_cool_radiative(&py->phys, dt);
}
