/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/11 12:12:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
/**
 * @brief Updates rotation and deformation for a sphere based on its velocity.
 */
/**
 * @brief Caches 1/scale for each axis for fast intersection.
 */
static void	cache_inv_scale(t_sphere *sp)
{
	sp->inv_scale.x = 1.0 / sp->transform.scale.x;
	sp->inv_scale.y = 1.0 / sp->transform.scale.y;
	sp->inv_scale.z = 1.0 / sp->transform.scale.z;
	sp->inv_scale.w = 0.0;
}

/**
 * @brief Applies squash-and-stretch deformation based on impulse delta-V.
 * Only reacts to sudden velocity changes above a threshold —
 * gravity drift and resting contact solver micro-corrections are filtered out.
 * squash decays each frame; axis of squash follows the dominant dv component.
 */
static void	apply_deformation(t_sphere *sp, t_vec3 dv)
{
	double	spike;
	double	q;

	spike = vec3_mag(dv);
	if (spike < 0.8)
		spike = 0.0;
	q = sp->phys.squash * 0.72;
	if (spike * 0.045 > q)
		q = spike * 0.045;
	if (q > 0.32)
		q = 0.32;
	sp->phys.squash = q;
	if (q < 0.012)
	{
		sp->transform.scale = vec3(1, 1, 1);
		sp->is_deformed = false;
		return ;
	}
	sp->is_deformed = true;
	if (fabs(dv.x) >= fabs(dv.y) && fabs(dv.x) >= fabs(dv.z))
		sp->transform.scale = vec3(1.0 - q, 1.0 + q * 0.5, 1.0 + q * 0.5);
	else if (fabs(dv.z) >= fabs(dv.y))
		sp->transform.scale = vec3(1.0 + q * 0.5, 1.0 + q * 0.5, 1.0 - q);
	else
		sp->transform.scale = vec3(1.0 + q * 0.5, 1.0 - q, 1.0 + q * 0.5);
}

/**
 * @brief Updates rotation and impulse-based deformation for a sphere.
 * Tracks the local frame axes (right/up/forward) via Rodrigues rotation so
 * the world-space angular velocity is projected onto the correct local axes.
 * This produces proper rolling behaviour rather than world-aligned sliding.
 */
static void	update_state(t_sphere *sp, double dt)
{
	t_vec3	w;
	t_vec3	r_d;
	t_vec3	dv;

	if (vec3_mag_sq(sp->transform.right) < 1e-9)
	{
		sp->transform.right = vec3(1, 0, 0);
		sp->transform.up = vec3(0, 1, 0);
		sp->transform.forward = vec3(0, 0, 1);
	}
	w = sp->phys.angular_velocity;
	sp->transform.right = vec3_norm(rot_by_ang(sp->transform.right, w, dt));
	sp->transform.up = vec3_norm(rot_by_ang(sp->transform.up, w, dt));
	sp->transform.forward = vec3_norm(rot_by_ang(sp->transform.forward, w, dt));
	r_d.x = vec3_dot(w, sp->transform.right);
	r_d.y = vec3_dot(w, sp->transform.up);
	r_d.z = vec3_dot(w, sp->transform.forward);
	r_d = vec3_scale(r_d, dt * 180.0 / M_PI);
	sp->transform.rotation.pitch += r_d.x;
	sp->transform.rotation.yaw += r_d.y;
	sp->transform.rotation.roll += r_d.z;
	dv = vec3_sub(sp->phys.velocity, sp->phys.prev_velocity);
	apply_deformation(sp, dv);
	cache_inv_scale(sp);
}

/**
 * @brief Integrates a sphere body through one time step.
 */
static void	apply_damp(t_sphere *sp, double dt, t_physics_settings *s)
{
	double	linear_d;
	double	angular_d;

	linear_d = clamp_d(1.0 - s->global_damping * dt, 0, 1);
	angular_d = clamp_d(1.0 - s->global_damping * 0.5 * dt, 0, 1);
	sp->phys.velocity = vec3_scale(vec3_add(vec3_add(sp->phys.velocity,
					vec3_scale(s->gravity, dt)),
				vec3_scale(sp->phys.accel, dt)), linear_d);
	sp->phys.angular_velocity = vec3_scale(sp->phys.angular_velocity,
			angular_d);
}

void	integrate_sphere(t_sphere *sp, double dt, t_physics_settings *s)
{
	if (sp->phys.is_static || sp->phys.is_sleeping)
		return ;
	check_sleep(&sp->phys, dt);
	if (sp->phys.is_sleeping)
		return ;
	if (vec3_mag_sq(sp->phys.inv_inertia) < 1e-9 && sp->radius_sq > 1e-9)
		sp->phys.inv_inertia = vec3(2.5 / sp->radius_sq,
				2.5 / sp->radius_sq, 2.5 / sp->radius_sq);
	else if (vec3_mag_sq(sp->phys.inv_inertia) < 1e-9)
		sp->phys.inv_inertia = vec3(1.0, 1.0, 1.0);
	clamp_accel(&sp->phys);
	apply_damp(sp, dt, s);
	clamp_speed(&sp->phys);
	sp->phys.accel = vec3(0, 0, 0);
	sp->phys.prev_velocity = sp->phys.velocity;
	sp->transform.pos = vec3_add(sp->transform.pos,
			vec3_scale(sp->phys.velocity, dt));
	update_state(sp, dt);
	sp->phys.pos = sp->transform.pos;
	sp->phys.center = sp->transform.pos;
	phys_heat_viscous(&sp->phys, dt);
	phys_cool_radiative(&sp->phys, dt);
}
