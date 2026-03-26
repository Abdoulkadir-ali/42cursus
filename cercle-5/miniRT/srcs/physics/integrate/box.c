/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* *****************:********************************************************* */

#include "physics.h"
#include "objects.h"

static void	init_box_inertia(t_box *bx)
{
	t_vec3	e;

	e = bx->half_extents;
	bx->phys.inv_inertia.x = 3.0 / (e.y * e.y + e.z * e.z + 1e-9);
	bx->phys.inv_inertia.y = 3.0 / (e.x * e.x + e.z * e.z + 1e-9);
	bx->phys.inv_inertia.z = 3.0 / (e.x * e.x + e.y * e.y + 1e-9);
}

/**
 * @brief Logic to update the box's orientation and position.
 * Uses global physics constants.
 */
void	integrate_box(t_box *bx, double dt)
{
	t_vec3	rot;

	if (bx->phys.is_static)
		return ;
	if (bx->phys.mass < 1e-6)
		bx->phys.mass = 1.0;
	if (vec3_mag_sq(bx->phys.inv_inertia) < 1e-9)
		init_box_inertia(bx);
	bx->phys.velocity = vec3_add(bx->phys.velocity,
			vec3_scale(GRAVITY_VEC, dt));
	bx->phys.velocity = vec3_scale(bx->phys.velocity,
			clamp_d(1.0 - GLOBAL_DAMPING * dt, 0, 1));
	bx->phys.angular_velocity = vec3_scale(bx->phys.angular_velocity,
			clamp_d(1.0 - GLOBAL_DAMPING * 0.5 * dt, 0, 1));
	rot = vec3_scale(bx->phys.angular_velocity, dt * (180.0 / M_PI));
	bx->transform.rotation.pitch += rot.x;
	bx->transform.rotation.yaw += rot.y;
	bx->transform.rotation.roll += rot.z;
	bx->transform.forward = vec3_norm(rot_by_ang(bx->transform.forward,
				bx->phys.angular_velocity, dt));
	bx->transform.pos = vec3_add(bx->transform.pos,
			vec3_scale(bx->phys.velocity, dt));
	bx->phys.center = bx->transform.pos;
}
