/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 21:05:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
/**
 * @brief Updates rotation and deformation for a sphere based on its velocity.
 */
/**
 * @brief Caches 1/scale for each axis so intersect_sphere avoids per-ray divisions.
 */
static void	cache_inv_scale(t_sphere *sp)
{
	sp->inv_scale.x = 1.0 / sp->transform.scale.x;
	sp->inv_scale.y = 1.0 / sp->transform.scale.y;
	sp->inv_scale.z = 1.0 / sp->transform.scale.z;
	sp->inv_scale.w = 0.0;
}

/**
 * @brief Updates rotation and deformation for a sphere based on its velocity.
 */
static void	update_state(t_sphere *sp, double dt)
{
	t_vec3	r_d;

	r_d = vec3_scale(sp->phys.angular_velocity, dt * 180.0 / M_PI);
	sp->transform.rotation.pitch += r_d.x;
	sp->transform.rotation.yaw += r_d.y;
	sp->transform.rotation.roll += r_d.z;
	if (vec3_mag(sp->phys.velocity) > 0.1)
	{
		sp->transform.scale = vec3(1.0 + fmin(vec3_mag(sp->phys.velocity)
						* 0.05, 0.3), 1.0, 1.0);
		sp->is_deformed = true;
	}
	else
	{
		sp->transform.scale = vec3(1, 1, 1);
		sp->is_deformed = false;
	}
	cache_inv_scale(sp);
}

/**
 * @brief Integrates a sphere body through one time step.
 */
void	integrate_sphere(t_sphere *sp, double dt, t_physics_settings *s)
{
	double	linear_d;
	double	angular_d;
	double	inv_i;

	if (sp->phys.is_static)
		return ;
	if (vec3_mag_sq(sp->phys.inv_inertia) < 1e-9)
	{
		inv_i = 1.0;
		if (sp->radius_sq > 1e-9)
			inv_i = 2.5 / sp->radius_sq;
		sp->phys.inv_inertia = vec3(inv_i, inv_i, inv_i);
	}
	linear_d = pow(1.0 - clamp_d(s->global_damping, 0, 1), dt);
	angular_d = pow(1.0 - clamp_d(s->global_damping, 0, 1) * 0.5, dt);
	sp->phys.velocity = vec3_scale(vec3_add(sp->phys.velocity,
				vec3_scale(s->gravity, dt)), linear_d);
	sp->phys.angular_velocity = vec3_scale(sp->phys.angular_velocity,
			angular_d);
	sp->transform.pos = vec3_add(sp->transform.pos,
			vec3_scale(sp->phys.velocity, dt));
	update_state(sp, dt);
	sp->phys.pos = sp->transform.pos;
	sp->phys.center = sp->transform.pos;
}
