/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/11 14:52:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Performs Rodrigues rotation of vector v by angular velocity w * dt.
 */
t_vec3	rot_by_ang(t_vec3 v, t_vec3 w, double dt)
{
	double	th;
	t_vec3	n;

	th = vec3_mag(w) * dt;
	if (th < 1e-9)
		return (v);
	n = vec3_norm(w);
	return (vec3_add(vec3_add(vec3_scale(v, cos(th)),
				vec3_scale(vec3_cross(n, v), sin(th))),
			vec3_scale(n, vec3_dot(n, v) * (1.0 - cos(th)))));
}

void	sync_phys_settings(t_scene *scene, t_physic_engine *engine)
{
	if (scene->scene_gravity_set)
		engine->settings.gravity = scene->scene_gravity;
	if (scene->scene_big_g_set)
		engine->settings.big_g = scene->scene_big_g;
	if (scene->scene_damping_set)
		engine->settings.global_damping = scene->scene_damping;
	if (scene->scene_wind_set)
		engine->settings.wind = scene->scene_wind;
	if (scene->scene_turbulence_set)
		engine->settings.wind_turbulence = scene->scene_turbulence;
}

void	check_sleep(t_physics_body *b, double dt)
{
	double	v_sq;
	double	w_sq;

	if (!b || b->is_static || b->is_sleeping)
		return ;
	v_sq = vec3_mag_sq(b->velocity);
	w_sq = vec3_mag_sq(b->angular_velocity);
	if (v_sq < 0.005 && w_sq < 0.05)
	{
		b->sleep_timer += dt;
		if (b->sleep_timer > 0.5)
		{
			b->is_sleeping = true;
			b->velocity = vec3(0, 0, 0);
			b->angular_velocity = vec3(0, 0, 0);
		}
	}
	else
		b->sleep_timer = 0.0;
}

void	wake_body(t_physics_body *b)
{
	if (!b || b->is_static)
		return ;
	b->is_sleeping = false;
	b->sleep_timer = 0.0;
}

/**
 * @brief Clamps body->accel to MAX_ACCEL magnitude.
 *        Gravitational attraction from a very massive neighbour can produce
 *        thousands of m/s² per step, launching the body through solid floors
 *        before the collision solver gets a chance to respond.
 *        Clamping preserves direction but caps the speed gain per frame.
 */
void	clamp_accel(t_physics_body *b)
{
	double	mag_sq;
	double	mag;

	mag_sq = vec3_mag_sq(b->accel);
	if (mag_sq > MAX_ACCEL * MAX_ACCEL)
	{
		mag = sqrt(mag_sq);
		b->accel = vec3_scale(b->accel, MAX_ACCEL / mag);
	}
}

void	clamp_speed(t_physics_body *b)
{
	double	mag_sq;
	double	mag;

	mag_sq = vec3_mag_sq(b->velocity);
	if (mag_sq > MAX_SPEED * MAX_SPEED)
	{
		mag = sqrt(mag_sq);
		b->velocity = vec3_scale(b->velocity, MAX_SPEED / mag);
	}
}
