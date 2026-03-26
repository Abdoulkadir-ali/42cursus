/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 10:35:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "objects.h"

/**
 * @brief Chef de Gare: Orchestrates the physics update for a single body.
 * Routes between Primitive linear motion and AAA rotational dynamics.
 * Synchronizes the visual t_transform with the physical t_physics_body.
 */
void	phys_dispatch_object(t_physics_body *b, t_transform *t, double dt)
{
	t_vec3	rot;

	if (b->is_static)
		return ;
	if (b->is_compound)
	{
		b->velocity = vec3_add(b->velocity, vec3_scale(gravity_vec(), dt));
		b->velocity = vec3_scale(b->velocity, pow(1.0 - GLOBAL_DAMPING, dt));
		t->pos = vec3_add(t->pos, vec3_scale(b->velocity, dt));
		b->center = t->pos;
		b->angular_velocity = vec3_scale(b->angular_velocity, 
				pow(1.0 - GLOBAL_DAMPING * 0.5, dt));
		rot = vec3_scale(b->angular_velocity, dt * (180.0 / M_PI));
		t->rotation.pitch += rot.x;
		t->rotation.yaw += rot.y;
		t->rotation.roll += rot.z;
		update_compound(b);
	}
}
