/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* *****************:********************************************************* */

#include "physics.h"
#include "objects.h"

static void	init_cylinder_inertia(t_cylinder *cy)
{
	double	r2;
	double	h2;

	r2 = cy->transform.scale.x * cy->transform.scale.x + 1e-9;
	h2 = 4.0 * cy->transform.scale.y * cy->transform.scale.y;
	cy->phys.inv_inertia.x = 12.0 / (3.0 * r2 + h2);
	cy->phys.inv_inertia.y = 2.0 / r2;
	cy->phys.inv_inertia.z = 12.0 / (3.0 * r2 + h2);
}

/**
 * @brief Logic to update the cylinder's position, rotation, and physical center.
 * Uses global physics constants.
 */
void	integrate_cylinder(t_cylinder *cy, double dt)
{
	t_vec3	rot;

	if (cy->phys.is_static)
		return ;
	if (cy->phys.mass < 1e-6)
		cy->phys.mass = 1.0;
	if (vec3_mag_sq(cy->phys.inv_inertia) < 1e-9)
		init_cylinder_inertia(cy);
	cy->phys.velocity = vec3_add(cy->phys.velocity,
			vec3_scale(GRAVITY_VEC, dt));
	cy->phys.velocity = vec3_scale(cy->phys.velocity,
			clamp_d(1.0 - GLOBAL_DAMPING * dt, 0, 1));
	cy->phys.angular_velocity = vec3_scale(cy->phys.angular_velocity,
			clamp_d(1.0 - GLOBAL_DAMPING * 0.5 * dt, 0, 1));
	rot = vec3_scale(cy->phys.angular_velocity, dt * (180.0 / M_PI));
	cy->transform.rotation.pitch += rot.x;
	cy->transform.rotation.yaw += rot.y;
	cy->transform.rotation.roll += rot.z;
	cy->transform.forward = vec3_norm(rot_by_ang(cy->transform.forward,
				cy->phys.angular_velocity, dt));
	cy->transform.pos = vec3_add(cy->transform.pos,
			vec3_scale(cy->phys.velocity, dt));
	cy->phys.center = vec3_add(cy->transform.pos,
			vec3_scale(vec3_norm(cy->transform.forward),
				cy->transform.scale.y * 0.5));
}
