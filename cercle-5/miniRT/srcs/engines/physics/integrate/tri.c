/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/07 01:45:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Initializes inertia for a triangle shape.
 */
static void	init_tri_inertia(t_tri_shape *tr)
{
	double	a2;
	double	b2;

	if (tr->phys.mass < 1e-6)
		tr->phys.mass = 1.0;
	if (vec3_mag_sq(tr->phys.inv_inertia) > 1e-9)
		return ;
	a2 = vec3_mag_sq(vec3_sub(tr->v[1], tr->v[0])) + 1e-9;
	b2 = vec3_mag_sq(vec3_sub(tr->v[2], tr->v[0])) + 1e-9;
	tr->phys.inv_inertia = vec3(18.0 / b2, 18.0 / (a2 + b2), 18.0 / a2);
}

/**
 * @brief Displaces triangle vertices to maintain world center.
 */
static void	apply_displace(t_tri_shape *tr, t_vec3 delta)
{
	size_t	i;

	i = 0;
	while (i < 3)
	{
		tr->v[i] = vec3_add(tr->v[i], delta);
		i++;
	}
	tr->xform.pos = vec3_add(tr->xform.pos, delta);
	tr->phys.center = tr->xform.pos;
}

/**
 * @brief Updates rotation and orientation for the triangle.
 */
static void	update_tri_rot(t_tri_shape *tr, double dt, t_vec3 rot_d,
		t_vec3 delta)
{
	size_t	i;

	tr->xform.rotation.pitch += rot_d.x;
	tr->xform.rotation.yaw += rot_d.y;
	tr->xform.rotation.roll += rot_d.z;
	tr->normal = rot_by_ang(tr->normal, tr->phys.angular_velocity, dt);
	i = 0;
	while (i < 3)
	{
		tr->v[i] = vec3_add(vec3_add(tr->xform.pos,
					rot_by_ang(vec3_sub(tr->v[i], tr->xform.pos),
						tr->phys.angular_velocity, dt)), delta);
		i++;
	}
}

/**
 * @brief Integrates a triangle body through one time step.
 */
void	integrate_tri(t_tri_shape *tr, double dt, t_physics_settings *s)
{
	t_vec3	delta;
	t_vec2	damp;
	t_vec3	rot;

	if (tr->phys.is_static)
		return ;
	init_tri_inertia(tr);
	delta = vec3_scale(vec3_add(vec3_add(tr->v[0], tr->v[1]), tr->v[2]),
			1.0 / 3.0);
	delta = vec3_sub(tr->xform.pos, delta);
	apply_displace(tr, delta);
	tr->phys.velocity = vec3_add(tr->phys.velocity, vec3_scale(s->gravity, dt));
	damp.x = clamp_d(1.0 - s->global_damping * dt, 0, 1);
	damp.y = clamp_d(1.0 - s->global_damping * 0.5 * dt, 0, 1);
	tr->phys.velocity = vec3_scale(tr->phys.velocity, damp.x);
	tr->phys.angular_velocity = vec3_scale(tr->phys.angular_velocity, damp.y);
	delta = vec3_scale(tr->phys.velocity, dt);
	rot = vec3_scale(tr->phys.angular_velocity, dt * (180.0 / M_PI));
	update_tri_rot(tr, dt, rot, delta);
	tr->xform.pos = vec3_add(tr->xform.pos, delta);
	tr->phys.center = tr->xform.pos;
	tr->phys.pos = tr->xform.pos;
}
