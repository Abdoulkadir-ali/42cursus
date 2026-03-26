/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* *****************:********************************************************* */

#include "physics.h"
#include "objects.h"

static void	init_capsule_inertia(t_capsule *cap)
{
	double	r2;
	double	h2;

	r2 = cap->radius * cap->radius + 1e-9;
	h2 = 4.0 * cap->half_height * cap->half_height;
	cap->phys.inv_inertia.x = 12.0 / (3.0 * r2 + h2);
	cap->phys.inv_inertia.y = 2.0 / r2;
	cap->phys.inv_inertia.z = 12.0 / (3.0 * r2 + h2);
}

/**
 * @brief Logic to update the capsule's position and orientation axis.
 * Uses global physics constants.
 */
void	integrate_capsule(t_capsule *cap, double dt)
{
	t_vec3	rot;

	if (cap->phys.is_static)
		return ;
	if (cap->phys.mass < 1e-6)
		cap->phys.mass = 1.0;
	if (vec3_mag_sq(cap->phys.inv_inertia) < 1e-9)
		init_capsule_inertia(cap);
	cap->phys.velocity = vec3_add(cap->phys.velocity,
			vec3_scale(GRAVITY_VEC, dt));
	cap->phys.velocity = vec3_scale(cap->phys.velocity,
			clamp_d(1.0 - GLOBAL_DAMPING * dt, 0, 1));
	cap->phys.angular_velocity = vec3_scale(cap->phys.angular_velocity,
			clamp_d(1.0 - GLOBAL_DAMPING * 0.5 * dt, 0, 1));
	rot = vec3_scale(cap->phys.angular_velocity, dt * (180.0 / M_PI));
	cap->transform.rotation.pitch += rot.x;
	cap->transform.rotation.yaw += rot.y;
	cap->transform.rotation.roll += rot.z;
	cap->axis = vec3_norm(rot_by_ang(cap->axis, cap->phys.angular_velocity, dt));
	cap->transform.pos = vec3_add(cap->transform.pos,
			vec3_scale(cap->phys.velocity, dt));
	cap->phys.center = cap->transform.pos;
}
