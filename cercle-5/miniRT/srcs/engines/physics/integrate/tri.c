/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	init_tri_inertia(t_tri_shape *tr)
{
	t_vec3	inv_i;
	double	a2;
	double	b2;

	a2 = vec3_mag_sq(vec3_sub(tr->v[1], tr->v[0])) + 1e-9;
	b2 = vec3_mag_sq(vec3_sub(tr->v[2], tr->v[0])) + 1e-9;
	inv_i.x = 18.0 / b2;
	inv_i.y = 18.0 / (a2 + b2);
	inv_i.z = 18.0 / a2;
	tr->phys.inv_inertia = mat3_diag(inv_i);
}

static void	update_tri_verts(t_tri_shape *tr, t_vec3 delta, double dt)
{
	int	i;

	tr->normal = rot_by_ang(tr->normal, tr->phys.angular_velocity, dt);
	i = -1;
	while (++i < 3)
		tr->v[i] = vec3_add(vec3_add(tr->transform.pos,
					rot_by_ang(vec3_sub(tr->v[i], tr->transform.pos),
						tr->phys.angular_velocity, dt)), delta);
}

/**
 * @brief Logic to update the triangle's physical state.
 * Uses global physics constants.
 */
void	integrate_tri(t_tri_shape *tr, double dt)
{
	t_vec3	delta;
	t_vec3	rot;

	if (tr->phys.is_static)
		return ;
	if (tr->phys.mass < 1e-6)
		tr->phys.mass = 1.0;
	init_tri_inertia(tr);
	tr->phys.velocity = vec3_add(tr->phys.velocity,
			vec3_scale(gravity_vec(), dt));
	tr->phys.velocity = vec3_scale(tr->phys.velocity,
			clamp_d(1.0 - GLOBAL_DAMPING * dt, 0, 1));
	tr->phys.angular_velocity = vec3_scale(tr->phys.angular_velocity,
			clamp_d(1.0 - GLOBAL_DAMPING * 0.5 * dt, 0, 1));
	delta = vec3_scale(tr->phys.velocity, dt);
	rot = vec3_scale(tr->phys.angular_velocity, dt * (180.0 / M_PI));
	tr->transform.rotation.pitch += rot.x;
	tr->transform.rotation.yaw += rot.y;
	tr->transform.rotation.roll += rot.z;
	update_tri_verts(tr, delta, dt);
	tr->transform.pos = vec3_add(tr->transform.pos, delta);
	tr->phys.center = tr->transform.pos;
}
