/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:07:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

static void	apply_deformation(t_sphere *sp)
{
	double		s;
	double		d;
	t_transform	x;

	s = vec3_mag(sp->phys.velocity);
	d = s * 0.05;
	if (d > 0.3)
		d = 0.3;
	if (s > 0.1)
	{
		sp->transform.scale = vec3(1.0 + d, 1.0 + d, 1.0 + d);
		sp->is_deformed = true;
		x.pos = sp->transform.pos;
		x.scale = sp->transform.scale;
		x.rotation = (t_rotator){0, 0, 0};
		sp->inv_transform = mat4_inverse_transform(x);
	}
	else
	{
		sp->transform.scale = vec3(1, 1, 1);
		sp->is_deformed = false;
	}
}

static void	ensure_mass_and_inertia(t_sphere *sp)
{
	double	ii;

	if (sp->phys.mass < 1e-6)
		sp->phys.mass = 1.0;
	if (sp->phys.inv_inertia.m[0][0] < 1e-9)
	{
		ii = 2.5 / (sp->radius_sq + 1e-9);
		sp->phys.inv_inertia = mat3_diag(vec3(ii, ii, ii));
	}
}

static void	apply_forces_and_damping(t_sphere *sp, double dt)
{
	sp->phys.velocity = vec3_add(sp->phys.velocity, vec3_scale(gravity_vec(),
				dt));
	sp->phys.velocity = vec3_scale(sp->phys.velocity, pow(1.0 - GLOBAL_DAMPING,
				dt));
	sp->phys.angular_velocity = vec3_scale(sp->phys.angular_velocity, pow(1.0
				- GLOBAL_DAMPING * 0.5, dt));
}

static void	update_transform_and_rotation(t_sphere *sp, double dt)
{
	t_vec3	rot;

	sp->transform.pos = vec3_add(sp->transform.pos,
			vec3_scale(sp->phys.velocity, dt));
	rot = vec3_scale(sp->phys.angular_velocity, dt * (180.0 / M_PI));
	sp->transform.rotation.pitch += rot.x;
	sp->transform.rotation.yaw += rot.y;
	sp->transform.rotation.roll += rot.z;
}

/**
 * @brief Logic to update the sphere's position and orientation based on
 * accumulated physical forces. Uses global physics constants.
 */
void	integrate_sphere(t_sphere *sp, double dt)
{
	if (sp->phys.is_static)
		return ;
	ensure_mass_and_inertia(sp);
	apply_forces_and_damping(sp, dt);
	update_transform_and_rotation(sp, dt);
	apply_deformation(sp);
	sp->phys.center = sp->transform.pos;
}
