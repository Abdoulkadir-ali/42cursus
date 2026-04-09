/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 20:48:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Recalculates inertia for a rectangle shape and standardizes mass.
 */
static void	init_rect_inertia(t_rect *rc)
{
	t_vec3	e0;
	t_vec3	e1;
	double	w2;
	double	h2;

	if (rc->phys.mass < 1e-6)
		rc->phys.mass = 1.0;
	if (vec3_mag_sq(rc->phys.inv_inertia) > 1e-9)
		return ;
	e0 = vec3_sub(rc->v[1], rc->v[0]);
	e1 = vec3_sub(rc->v[3], rc->v[0]);
	w2 = vec3_mag_sq(e0) + 1e-9;
	h2 = vec3_mag_sq(e1) + 1e-9;
	rc->phys.inv_inertia = vec3(12.0 / h2, 12.0 / (w2 + h2), 12.0 / w2);
}

/**
 * @brief Displaces rectangle vertices and sets up center.
 */
static void	apply_displace(t_rect *rc, t_vec3 delta)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		rc->v[i] = vec3_add(rc->v[i], delta);
		i++;
	}
	rc->transform.pos = vec3_add(rc->transform.pos, delta);
	rc->phys.center = rc->transform.pos;
}

/**
 * @brief Updates rotation and orientation for the rectangle.
 */
static void	update_rect_rot(t_rect *rc, double dt, t_vec3 rot_d, t_vec3 delta)
{
	size_t	i;

	rc->transform.rotation.pitch += rot_d.x;
	rc->transform.rotation.yaw += rot_d.y;
	rc->transform.rotation.roll += rot_d.z;
	rc->normal = rot_by_ang(rc->normal, rc->phys.angular_velocity, dt);
	i = 0;
	while (i < 4)
	{
		rc->v[i] = vec3_add(vec3_add(rc->transform.pos,
					rot_by_ang(vec3_sub(rc->v[i], rc->transform.pos),
						rc->phys.angular_velocity, dt)), delta);
		i++;
	}
}

/**
 * @brief Integrates a rectangle through one time step.
 */
void	integrate_rect(t_rect *rc, double dt, t_physics_settings *s)
{
	t_vec3	delta;
	t_vec2	damp;

	if (rc->phys.is_static)
		return ;
	init_rect_inertia(rc);
	delta = vec3_sub(rc->transform.pos, vec3_scale(vec3_add(vec3_add(rc->v[0],
						rc->v[1]), vec3_add(rc->v[2], rc->v[3])), 0.25));
	apply_displace(rc, delta);
	rc->phys.velocity = vec3_add(rc->phys.velocity,
			vec3_add(vec3_scale(s->gravity, dt),
				vec3_scale(rc->phys.accel, dt)));
	rc->phys.accel = vec3(0, 0, 0);
	damp.x = clamp_d(1.0 - s->global_damping * dt, 0, 1);
	damp.y = clamp_d(1.0 - s->global_damping * 0.5 * dt, 0, 1);
	rc->phys.velocity = vec3_scale(rc->phys.velocity, damp.x);
	rc->phys.angular_velocity = vec3_scale(rc->phys.angular_velocity, damp.y);
	delta = vec3_scale(rc->phys.velocity, dt);
	update_rect_rot(rc, dt, vec3_scale(rc->phys.angular_velocity,
			dt * (180.0 / M_PI)), delta);
	rc->transform.pos = vec3_add(rc->transform.pos, delta);
	rc->phys.center = rc->transform.pos;
	rc->phys.pos = rc->transform.pos;
}
