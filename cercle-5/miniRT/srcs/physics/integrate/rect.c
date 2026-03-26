/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 10:35:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "objects.h"

static void	init_rect_inertia(t_rect *rc)
{
	t_vec3	e0;
	t_vec3	e1;
	double	w2;
	double	h2;

	if (vec3_mag_sq(rc->phys.inv_inertia) > 1e-9)
		return ;
	e0 = vec3_sub(rc->v[1], rc->v[0]);
	e1 = vec3_sub(rc->v[3], rc->v[0]);
	w2 = vec3_mag_sq(e0) + 1e-9;
	h2 = vec3_mag_sq(e1) + 1e-9;
	rc->phys.inv_inertia.x = 12.0 / h2;
	rc->phys.inv_inertia.y = 12.0 / (w2 + h2);
	rc->phys.inv_inertia.z = 12.0 / w2;
}

static void	update_rect_verts(t_rect *rc, t_vec3 delta, double dt)
{
	int	i;

	rc->normal = rot_by_ang(rc->normal, rc->phys.angular_velocity, dt);
	i = -1;
	while (++i < 4)
		rc->v[i] = vec3_add(vec3_add(rc->transform.pos,
					rot_by_ang(vec3_sub(rc->v[i], rc->transform.pos),
						rc->phys.angular_velocity, dt)), delta);
}

/**
 * @brief Logic to update the rectangle's position, vertices, and orientation.
 * Uses global physics constants.
 */
void	integrate_rect(t_rect *rc, double dt)
{
	t_vec3	delta;
	t_vec3	rot;

	if (rc->phys.is_static)
		return ;
	if (rc->phys.mass < 1e-6)
		rc->phys.mass = 1.0;
	init_rect_inertia(rc);
	rc->phys.velocity = vec3_add(rc->phys.velocity,
			vec3_scale(gravity_vec(), dt));
	rc->phys.velocity = vec3_scale(rc->phys.velocity,
			clamp_d(1.0 - GLOBAL_DAMPING * dt, 0, 1));
	rc->phys.angular_velocity = vec3_scale(rc->phys.angular_velocity,
			clamp_d(1.0 - GLOBAL_DAMPING * 0.5 * dt, 0, 1));
	delta = vec3_scale(rc->phys.velocity, dt);
	rot = vec3_scale(rc->phys.angular_velocity, dt * (180.0 / M_PI));
	rc->transform.rotation.pitch += rot.x;
	rc->transform.rotation.yaw += rot.y;
	rc->transform.rotation.roll += rot.z;
	update_rect_verts(rc, delta, dt);
	rc->transform.pos = vec3_add(rc->transform.pos, delta);
	rc->phys.center = rc->transform.pos;
}
